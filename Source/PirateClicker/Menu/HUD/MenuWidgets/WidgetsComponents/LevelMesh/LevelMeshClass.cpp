// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/WidgetsComponents/LevelMesh/LevelMeshClass.h"
#include "Components/StaticMeshComponent.h"

ALevelMeshClass::ALevelMeshClass()
{
	PrimaryActorTick.bCanEverTick = false;
    
    SceneRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(SceneRootComponent);
    
    MeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh storage component"));
    MeshStorage->SetupAttachment(RootComponent);
}

void ALevelMeshClass::BeginPlay()
{
	Super::BeginPlay();
	
}


