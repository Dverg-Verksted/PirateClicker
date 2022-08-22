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

    SetStorageStaticMesh();

    
}

int32 AGoldStorageActor::GetCurrentGold()
{
    return CurrentGold;
}
void AGoldStorageActor::SetCurrentGold(float GoldToSet)
{
    CurrentGold = GoldToSet;
}

void AGoldStorageActor::SetStorageStaticMesh()
{
    if (!StaticMeshToChange) return;
    
    StaticMeshToChange->SetStaticMesh(StorageStaticMesh);
}
void AGoldStorageActor::PirateMovingDirectionChange()
{
    
}

