// This section is the property of the Dverg Verksted team


#include "Game/ScreenTap/ScreenTapActor.h"
#include "Library/PirateClickerLibrary.h"

// Sets default values
AScreenTapActor::AScreenTapActor()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Scene Root component"));
    SetRootComponent(SceneRootComponent);
    MeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh storage"));
    MeshStorage->SetupAttachment(SceneRootComponent);
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Widget component"));
    WidgetComponent->SetupAttachment(SceneRootComponent);
}

// BeginPlay
void AScreenTapActor::BeginPlay()
{
	Super::BeginPlay();

    SetLifeSpan(ActorLifeSpanTime);
}

