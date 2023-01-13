// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/WidgetsComponents/LevelMesh/LevelMeshClass.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"

ALevelMeshClass::ALevelMeshClass()
{
	PrimaryActorTick.bCanEverTick = false;
    
    SceneRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(SceneRootComponent);
    
    LevelMeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh storage component"));
    LevelMeshStorage->SetupAttachment(RootComponent);

    LevelMeshCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("Camera component"));
    LevelMeshCamera->SetupAttachment(RootComponent);
}

void ALevelMeshClass::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelMeshClass::RotateLevelMeshLeft()
{
    RotateLevelMeshLeftNotify.Broadcast();
    LevelMeshStorage->SetRelativeRotation(LevelMeshStorage->GetRelativeRotation() + LevelMeshRotationRate);
    
}
void ALevelMeshClass::RotateLevelMeshRight()
{
    RotateLevelMeshRightNotify.Broadcast();
    LevelMeshStorage->SetRelativeRotation(LevelMeshStorage->GetRelativeRotation() - LevelMeshRotationRate);
    
}


