// This section is the property of the Dverg Verksted team

#include "Game/GoldStorage/GoldStorageActor.h"
#include "Library/PirateClickerLibrary.h"
#include "Game/AI/Pirates/PirateActorBase.h"

// Sets default values
AGoldStorageActor::AGoldStorageActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    MeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh storage component"));
    MeshStorage->SetupAttachment(RootScene);

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Collision"));
    BoxCollision->SetupAttachment(RootScene);
    BoxCollision->SetBoxExtent(FVector(BoxCollisionSize));

    SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collision"));
    SphereCollision->SetupAttachment(RootScene);
    SphereCollision->SetSphereRadius(SphereCollisionRadius);
}

void AGoldStorageActor::BeginPlay()
{
    Super::BeginPlay();

    MaxGold = CurrentGold;
    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(MeshStorage != nullptr, "Mesh storage is nullptr")) return;

    if (isBoxCollision)
    {
        SphereCollision->DestroyComponent();
    }
    else
    {
        BoxCollision->DestroyComponent();
    }

    OnActorBeginOverlap.AddDynamic(this, &ThisClass::RegisterActorBeginOverlap);
    OnActorEndOverlap.AddDynamic(this, &ThisClass::RegisterActorEndOverlap);
}

int32 AGoldStorageActor::GetCurrentGold()
{
    return CurrentGold;
}

void AGoldStorageActor::SetCurrentGold(const int32 GoldToSet)
{
    CurrentGold = FMath::Clamp(GoldToSet, 0, MaxGold);
    OnChangeGoldCount();
}

void AGoldStorageActor::UpperCountGold()
{
    CurrentGold = FMath::Clamp(CurrentGold + 1, 0, MaxGold);
    OnChangeGoldCount();
}

#if WITH_EDITOR
void AGoldStorageActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!PropertyChangedEvent.Property) return;
    LOG_PIRATE(ELogVerb::Warning, FString::Printf(TEXT("Name Property[%s]"), *PropertyChangedEvent.Property->GetName()));

    if (PropertyChangedEvent.Property->GetName() == TEXT("MeshToChange"))
    {
        if (!MeshToChange) return;
        MeshStorage->SetStaticMesh(MeshToChange);
    }

    if (PropertyChangedEvent.Property->GetName() == TEXT("BoxCollisionSize"))
    {
        BoxCollision->SetBoxExtent(FVector(BoxCollisionSize));
    }
    if (PropertyChangedEvent.Property->GetName() == TEXT("SphereCollisionRadius"))
    {
        SphereCollision->SetSphereRadius(SphereCollisionRadius);
    }

    CollisionChecker();
}
#endif

void AGoldStorageActor::RegisterActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor->IsA(APirateActorBase::StaticClass()))
    {
        APirateActorBase* PirateBase = Cast<APirateActorBase>(OtherActor);
        if (!CHECKED(PirateBase != nullptr, "Cast to class APirateActorBase is fail")) return;
        if (!CHECKED(!ArrayTargetPirate.Contains(PirateBase), "Pirate actor is overlaped")) return;

        PirateBase->SetupStateBrain(EStateBrain::WalkToBack);
        if (CurrentGold != 0)
        {
            if (PirateBase->bHasTreasure) return;
            PirateBase->bHasTreasure = true;
            PirateBase->SpawnGoldChest(GoldChestToGive, this);
            GoldStorageChestTaken.Broadcast(PirateBase, this);
            SetCurrentGold(CurrentGold - 1);
            if (CurrentGold == 0)
            {
                GoldStorageEmpty.Broadcast();
            }
        }

        ArrayTargetPirate.Add(PirateBase);
        LOG_PIRATE(ELogVerb::Display, FString::Printf(TEXT("CurrentGold : [%i]"), CurrentGold));
    }
}

void AGoldStorageActor::RegisterActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor->IsA(APirateActorBase::StaticClass()))
    {
        ArrayTargetPirate.Remove(Cast<APirateActorBase>(OtherActor));
    }
}

void AGoldStorageActor::CollisionChecker()
{
    switch (TypeCollision)
    {
        case ETypeCollision::Box:
        {
            isBoxCollision = true;
            BoxCollision->SetVisibility(true);
            SphereCollision->SetVisibility(false);
            break;
        }
        case ETypeCollision::Sphere:
        {
            isBoxCollision = false;
            BoxCollision->SetVisibility(false);
            SphereCollision->SetVisibility(true);
            break;
        }
    }
}
