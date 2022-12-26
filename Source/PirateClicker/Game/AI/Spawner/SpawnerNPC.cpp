// This section is the property of the Dverg Verksted team

#include "Game/AI/Spawner/SpawnerNPC.h"
#include "DrawDebugHelpers.h"
#include "SplineActor.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Engine/AssetManager.h"
#include "Game/AI/DataAsset/PirateDataAsset.h"
#include "Game/AI/Pirates/PirateActorBase.h"
#include "Game/GoldStorage/GoldStorageActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_SpawnerNPC(TEXT("Pirate.ShowDebugSpawnerNPC"), false, TEXT("Enable the display of debag information on SpawnerNPC from canvas panel"), ECVF_Cheat);
#endif

#pragma region Default

void ASpawnerNPC::Print_LogSpawner(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function) const
{
    UPirateClickerLibrary::Print_Log(LogVerb, FString::Printf(TEXT("Name: [%s] | %s"), *GetName(), *Text), Line, Function);
}

// Sets default values
ASpawnerNPC::ASpawnerNPC()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    Billboard = CreateDefaultSubobject<UBillboardComponent>(FName("Billboard"));
    Billboard->SetupAttachment(RootScene);

    SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Sphere collision"));
    SphereCollision->SetupAttachment(RootScene);
    SphereCollision->SetSphereRadius(RadiusCollision);
}

void ASpawnerNPC::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_SpawnerNPC.GetValueOnGameThread())
    {
        for (auto Pos : ArrSavedPosition)
        {
            DrawDebugSphere(GetWorld(), Pos, 12.0f, 12, FColor::Red, false, 0.0f, 0, 2.0f);
        }
    }
#endif
}

// Called when the game starts or when spawned
void ASpawnerNPC::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(Billboard != nullptr, "Billboard is nullptr")) return;
    if (!CHECKED(SphereCollision != nullptr, "Sphere Collision is nullptr")) return;

    ArrSavedPosition = GeneratePositionPoint(CountSpawnPosition);

    OnActorBeginOverlap.AddDynamic(this, &ThisClass::RegisterBeginOverlapActor);
}

void ASpawnerNPC::RegisterBeginOverlapActor(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor->IsA(APirateActorBase::StaticClass()))
    {
        APirateActorBase* PirateActorBase = Cast<APirateActorBase>(OtherActor);
        if (!PirateActorBase) return;
        if (PirateActorBase->bHasTreasure)
        {
            OnLostTreasureNotify.Broadcast();
        }

        if (PirateActorBase->GetStateBrain() == EStateBrain::WalkToBack)
        {
            RegisterPirateDead(PirateActorBase);
            PirateActorBase->SetLifeSpan(1.0f);
        }
    }
}

#if WITH_EDITOR

void ASpawnerNPC::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!PropertyChangedEvent.Property) return;

    if (PropertyChangedEvent.GetPropertyName() == TEXT("RadiusCollision"))
    {
        SphereCollision->SetSphereRadius(RadiusCollision);
    }

    if (PropertyChangedEvent.GetPropertyName() == TEXT("CountSpawnPosition"))
    {
        ArrSavedPosition = GeneratePositionPoint(CountSpawnPosition);
    }
}

#endif

#pragma endregion

#pragma region Action

void ASpawnerNPC::AddDataSpawn(const FDataPirateSpawn& DataPirateSpawn)
{
    QueueDataUnderWaves.Enqueue(DataPirateSpawn);
    CheckedDataUnderWaves();
}

void ASpawnerNPC::CheckedDataUnderWaves()
{
    if (GetWorldTimerManager().TimerExists(TimerHandleSpawnPirate) || QueueDataUnderWaves.IsEmpty()) return;

    GetWorldTimerManager().SetTimer(TimerHandleSpawnPirate, this, &ThisClass::RunSpawnPirate_Event, QueueDataUnderWaves.Peek()->DelayTimeSpawn, false);
}

void ASpawnerNPC::RunSpawnPirate_Event()
{
    FDataPirateSpawn DataPirateSpawn;
    QueueDataUnderWaves.Dequeue(DataPirateSpawn);
    LOG_SPAWNER(ELogVerb::Display, FString::Printf(TEXT("Run data pirate spawn: [%s]"), *DataPirateSpawn.ToString()));
    RunSpawnPirate(DataPirateSpawn.PirateAsset, DataPirateSpawn.CountSpawn);
    GetWorldTimerManager().ClearTimer(TimerHandleSpawnPirate);
    CheckedDataUnderWaves();
}

void ASpawnerNPC::RunSpawnPirate(const FSoftObjectPath& PirateAsset, const int32 CountSpawn)
{
    ArrSavedPosition = GeneratePositionPoint(CountSpawn);

    FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
    const FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnSpawnPirateComplete, PirateAsset, CountSpawn);
    AssetLoader.RequestAsyncLoad(PirateAsset, Delegate);
}

void ASpawnerNPC::RegisterPirateDead(APirateActorBase* Pirate)
{
    ArrayPirates.Remove(Pirate);
    if (ArrayPirates.Num() == 0 && QueueDataUnderWaves.IsEmpty())
    {
        LOG_SPAWNER(ELogVerb::Display, "All pirate dead on spawner");
        OnCompleteWorkSpawner.Broadcast(this);
    }
}

void ASpawnerNPC::OnSpawnPirateComplete(const FSoftObjectPath PirateAsset, const int32 CountSpawn)
{
    const UPirateDataAsset* PirateDataAsset = LoadObject<UPirateDataAsset>(nullptr, *(PirateAsset.ToString()));
    if (!CHECKED(PirateDataAsset != nullptr, FString::Printf(TEXT("Load pirate data asset failed for path: [%s]"), *PirateAsset.ToString()))) return;

    const TSubclassOf<APirateActorBase> SubClassPirate = PirateDataAsset->GetDataPirate().SubClassPirate;
    if (!CHECKED(SubClassPirate.GetDefaultObject() != nullptr, FString::Printf(TEXT("Sub class failed for path: [%s]"), *PirateAsset.ToString()))) return;

    for (int32 i = 0; i < CountSpawn; i++)
    {
        OnSpawnPirate_Event(PirateDataAsset, SubClassPirate);
    }
}

void ASpawnerNPC::OnSpawnPirate_Event(const UPirateDataAsset* PirateDataAsset, const TSubclassOf<APirateActorBase> SubClassPirate)
{
    FTransform Transform;
    ASplineActor* TargetSplineActor = GetRandomTargetSpline();
    if (!TargetSplineActor)
    {
        FTimerHandle TimerHandle;
        const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::OnSpawnPirate_Event, PirateDataAsset, SubClassPirate);
        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
        return;
    }

    FVector LocationSpawn = TargetSplineActor->GetSpline()->GetWorldLocationAtSplinePoint(0);
    LocationSpawn.Z += PirateDataAsset->GetDataPirate().SubClassPirate.GetDefaultObject()->GetCapsuleCollision()->GetScaledCapsuleHalfHeight();
    Transform.SetLocation(LocationSpawn);

    APirateActorBase* Pirate = GetWorld()->SpawnActorDeferred<APirateActorBase>(SubClassPirate, Transform);
    if (!CHECKED(Pirate != nullptr, FString::Printf(TEXT("Spawn pirate faild from subclass: [%s]"), *SubClassPirate->GetName()))) return;

    Pirate->InitParamsPirate(PirateDataAsset->GetDataPirate(), TargetSplineActor);
    Pirate->FinishSpawning(Transform);
    Pirate->OnPirateDead.AddDynamic(this, &ThisClass::RegisterPirateDead);
    ArrayPirates.Add(Pirate);
}

TArray<FVector> ASpawnerNPC::GeneratePositionPoint(const int32 CountSpawn) const
{
    TArray<FVector> Result;

    for (int32 i = 0; i < CountSpawn; i++)
    {
        const FVector ResCalcPos = CalculateRandomPositionSpawn();
        Result.Add(ResCalcPos);
        LOG_SPAWNER(ELogVerb::Display, FString::Printf(TEXT("Index #%i - [%s]"), i, *ResCalcPos.ToString()));
    }
    return Result;
}

FVector ASpawnerNPC::CalculateRandomPositionSpawn() const
{
    const FVector& L_CenterLoc = GetActorLocation();
    const FVector Box = FVector(RadiusCollision / 2.0f, RadiusCollision / 2.0f, 0.0f);

    const FVector BoxMin = L_CenterLoc - Box;
    const FVector BoxMax = L_CenterLoc + Box;
    const FVector L_RandPoint = FMath::RandPointInBox(FBox(BoxMin, BoxMax));
    const FVector L_EndPoint = L_RandPoint - FVector(0.0f, 0.0f, RadiusCollision * 6.0f);

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(this);
    CollisionQueryParams.AddIgnoredComponent(SphereCollision);

    FCollisionResponseParams CollisionResponseParams;
    GetWorld()->LineTraceSingleByChannel(HitResult, L_RandPoint, L_EndPoint, ECollisionChannel::ECC_Visibility, CollisionQueryParams, CollisionResponseParams);

    if (HitResult.bBlockingHit) return HitResult.Location;
    return FVector::ZeroVector;
}

FVector ASpawnerNPC::GetRandomPositionFromSavePosition()
{
    if (ArrSavedPosition.Num() == 0) return GetActorLocation();
    return ArrSavedPosition[FMath::RandRange(0, ArrSavedPosition.Num() - 1)];
}

ASplineActor* ASpawnerNPC::GetRandomTargetSpline()
{
    float MinDist = MAX_FLT;
    FDataSplineInfo TargetDataSplineInfo;
    for (const FDataSplineInfo& DataSplineInfo : ArrDataSplineInfo)
    {
        if (DataSplineInfo.Distance < MinDist && DataSplineInfo.TargetGoldStorage.Get() && DataSplineInfo.TargetGoldStorage.Get()->GetCurrentGold() != 0)
        {
            MinDist = DataSplineInfo.Distance;
            TargetDataSplineInfo = DataSplineInfo;
        }
    }

    auto* FindElem = ArrDataSplineInfo.FindByPredicate([TargetDataSplineInfo](const FDataSplineInfo& Data) { return TargetDataSplineInfo.Distance == Data.Distance; });

    for (auto*& Spline : FindElem->SplineActors)
    {
        if (!FindElem->BusySplineActors.Contains(Spline))
        {
            FindElem->BusySplineActors.Add(Spline);

            FTimerHandle TimerHandle;
            GetWorldTimerManager().SetTimer(
                TimerHandle, [FindElem, Spline]() { FindElem->BusySplineActors.Remove(Spline); }, 1.0f, false);

            return Spline;
        }
    }

    return nullptr;
}

void ASpawnerNPC::CompileSpline()
{
    ArrSavedPosition = GeneratePositionPoint(CountSpawnPosition);

    for (auto& SplineInfo : ArrDataSplineInfo)
    {
        if (!SplineInfo.TargetGoldStorage.Get()) continue;
        SplineInfo.Distance = (SplineInfo.TargetGoldStorage.Get()->GetActorLocation() - GetActorLocation()).Size();
        for (auto*& Spline : SplineInfo.SplineActors)
        {
            if (Spline != nullptr) continue;

            UWorld* World = UPirateClickerLibrary::GetWorldInEditor();
            if (!World) continue;

            Spline = World->SpawnActor<ASplineActor>();
            if (!Spline) continue;
            const FVector& StartPosSpline = GetRandomPositionFromSavePosition();
            const FVector& EndPosSpline = SplineInfo.TargetGoldStorage.Get()->GetActorLocation();
            Spline->SetActorLocation(StartPosSpline);

            if (!Spline->GetSpline()) continue;
            Spline->GetSpline()->AddSplineWorldPoint(FMath::Lerp(StartPosSpline, EndPosSpline, 0.2f));
            Spline->GetSpline()->AddSplineWorldPoint(FMath::Lerp(StartPosSpline, EndPosSpline, 0.4f));
            Spline->GetSpline()->AddSplineWorldPoint(FMath::Lerp(StartPosSpline, EndPosSpline, 0.6f));
            Spline->GetSpline()->AddSplineWorldPoint(FMath::Lerp(StartPosSpline, EndPosSpline, 0.8f));
            Spline->GetSpline()->AddSplineWorldPoint(FMath::Lerp(StartPosSpline, EndPosSpline, 1.0f));
        }
    }
}

void ASpawnerNPC::RemoveAllSpline()
{
    UWorld* World = UPirateClickerLibrary::GetWorldInEditor();
    if (!World) return;
    TArray<ASplineActor*> SplineActors;
    UPirateClickerLibrary::FindAllActors<ASplineActor>(World, SplineActors);
    for (auto Spline : SplineActors)
    {
        if (!Spline) return;
        Spline->Destroy();
        Spline = nullptr;
    }

    for (auto& SplineInfo : ArrDataSplineInfo)
    {
        if (!SplineInfo.TargetGoldStorage.Get()) continue;
        for (auto*& Spline : SplineInfo.SplineActors)
        {
            Spline = nullptr;
        }
    }
}

#pragma endregion