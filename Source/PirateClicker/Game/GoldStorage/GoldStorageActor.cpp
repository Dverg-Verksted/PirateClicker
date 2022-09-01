// This section is the property of the Dverg Verksted team


#include "Game/GoldStorage/GoldStorageActor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
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
}

int32 AGoldStorageActor::GetCurrentGold()
{
    return CurrentGold;
}
void AGoldStorageActor::SetCurrentGold(float GoldToSet)
{
    CurrentGold = GoldToSet;
}

#if WITH_EDITOR
void AGoldStorageActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!PropertyChangedEvent.Property) return;
    LOG_PIRATE(ELogRSVerb::Warning, FString::Printf(TEXT("Name Property[%s]"),*PropertyChangedEvent.Property->GetName()));

    if (PropertyChangedEvent.Property->GetName()==TEXT("MeshToChange"))
    {
        if (!MeshToChange) return;
        MeshStorage->SetStaticMesh(MeshToChange);
    }

    if (PropertyChangedEvent.Property->GetName()==TEXT("BoxCollisionSize"))
    {
        BoxCollision->SetBoxExtent(FVector(BoxCollisionSize));
    }
    if (PropertyChangedEvent.Property->GetName()==TEXT("SphereCollisionRadius"))
    {
        SphereCollision->SetSphereRadius(SphereCollisionRadius);
    }

    CollisionChecker();
    
}
#endif

void AGoldStorageActor::RegisterActorBeginOverlap(AActor* OverlappedActor,AActor* OtherActor)
{
    if (OtherActor && OtherActor->IsA(APirateActorBase::StaticClass()))
    {
        APirateActorBase* PirateBase = Cast<APirateActorBase>(OtherActor);
        if (!CHECKED(PirateBase != nullptr, "Cast to class APirateActorBase is fail")) return;
        PirateBase->SetupStateBrain(EStateBrain::WalkToBack);
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