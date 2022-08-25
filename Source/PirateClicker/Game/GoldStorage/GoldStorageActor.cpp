// This section is the property of the Dverg Verksted team


#include "Game/GoldStorage/GoldStorageActor.h"
#include "Components/StaticMeshComponent.h"
#include "Library/PirateClickerLibrary.h"

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
    
}

void AGoldStorageActor::BeginPlay()
{
	Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(MeshStorage != nullptr, "Mesh storage is nullptr")) return;
    
}

int32 AGoldStorageActor::GetCurrentGold()
{
    return CurrentGold;
}
void AGoldStorageActor::SetCurrentGold(float GoldToSet)
{
    CurrentGold = GoldToSet;
}

void AGoldStorageActor::CollisionChecker()
{
    if (TypeCollision == ETypeCollision::Box)
    {
        MeshStorage->DestroyComponent();
    }
    if (TypeCollision == ETypeCollision::Sphere)
    {
        MeshStorage->DestroyComponent();
    }
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
    
}
#endif

void AGoldStorageActor::OnActorBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
