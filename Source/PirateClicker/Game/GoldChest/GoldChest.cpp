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

