// This section is the property of the Dverg Verksted team


#include "Game/ScreenTap/ScreenTapActor.h"
#include "Library/PirateClickerLibrary.h"

// Sets default values
AScreenTapActor::AScreenTapActor()
{
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Scene Root component"));
    MeshStorage = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh storage"));
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Widget component"));
}

// BeginPlay
void AScreenTapActor::BeginPlay()
{
	Super::BeginPlay();

    ActorLifeSpanTime = 3.0f;
    SetLifeSpan(ActorLifeSpanTime);
	
}

void AScreenTapActor::SpawnActorByTap(FVector TapLocation)
{
    AScreenTapActor* TapActor= GetWorld()->SpawnActor<AScreenTapActor>();
    TapActor->AttachToComponent(SceneRootComponent,FAttachmentTransformRules::KeepRelativeTransform);
    TapActor->SetActorLocation(TapLocation);
}

