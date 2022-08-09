// This section is the property of the Dverg Verksted team

#include "Game/AI/Spawner/SpawnerNPC.h"

#include "DrawDebugHelpers.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_SpawnerNPC(TEXT("Pirate.ShowDebugSpawnerNPC"), false, TEXT("Enable the display of debag information on SpawnerNPC from canvas panel"), ECVF_Cheat);
#endif

#pragma region Default

void ASpawnerNPC::Print_LogSpawner(const ELogRSVerb LogVerb, const FString Text, const int Line, const char* Function) const
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

    ArrSavedPosition = GeneratePositionPoint();
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
}

#endif

#pragma endregion

TArray<FVector> ASpawnerNPC::GeneratePositionPoint() const
{
    TArray<FVector> Result;
    
    for (int32 i = 0; i < CountSpawnPosition; i++)
    {
        const FVector ResCalcPos = CalculateRandomPositionSpawn();
        Result.Add(ResCalcPos);
        LOG_SPAWNER(ELogRSVerb::Display, FString::Printf(TEXT("Index #%i - [%s]"), i, *ResCalcPos.ToString()));
    }
    return Result;
}

FVector ASpawnerNPC::CalculateRandomPositionSpawn() const
{
    const FVector& L_CenterLoc = GetActorLocation();
    const FVector Box = FVector(RadiusCollision / 2.0f,RadiusCollision / 2.0f, 0.0f);
	
    const FVector BoxMin = L_CenterLoc - Box;
    const FVector BoxMax = L_CenterLoc + Box;
    const FVector L_RandPoint = FMath::RandPointInBox(FBox(BoxMin, BoxMax));
    const FVector L_EndPoint = L_RandPoint - FVector(0.0f, 0.0f, RadiusCollision * 6.0f);

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(this);
    CollisionQueryParams.AddIgnoredComponent(SphereCollision);
	
    FCollisionResponseParams CollisionResponseParams;
    GetWorld()->LineTraceSingleByChannel(HitResult, L_RandPoint, L_EndPoint, ECollisionChannel::ECC_Visibility,
        CollisionQueryParams, CollisionResponseParams);
    
    if (HitResult.bBlockingHit)
        return HitResult.Location;
    return FVector::ZeroVector;
}
