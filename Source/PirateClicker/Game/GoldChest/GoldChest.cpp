// This section is the property of the Dverg Verksted team


#include "Game/GoldChest/GoldChest.h"
#include "Components/StaticMeshComponent.h"
#include "Library/PirateClickerLibrary.h"

AGoldChest::AGoldChest()
{
	PrimaryActorTick.bCanEverTick = false;

//creating subobjects for chest actor
    SceneRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(SceneRootComponent);

    MeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh storage component"));
    MeshStorage->SetupAttachment(RootComponent);
    
}

void AGoldChest::BeginPlay()
{
	Super::BeginPlay();

//Checkers
    if (!CHECKED(RootComponent != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(MeshStorage != nullptr, "Mesh storage is nullptr")) return;
	
}

//Chest state get
EGoldChestState AGoldChest::GetGoldChestState()
{
    return ChestState;
}

#if WITH_EDITOR

void AGoldChest::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

//Chest mesh change function
    if (PropertyChangedEvent.Property->GetName() == TEXT("MeshToChange"))
    {
        if (!MeshToChange) return;
        MeshStorage->SetStaticMesh(MeshToChange);
    }
}

#endif