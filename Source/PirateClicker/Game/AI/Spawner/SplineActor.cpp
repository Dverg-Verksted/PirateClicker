// This section is the property of the Dverg Verksted team


#include "Game/AI/Spawner/SplineActor.h"
#include "Components/SplineComponent.h"
#include "Library/PirateClickerLibrary.h"

// Sets default values
ASplineActor::ASplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline component"));
    SetRootComponent(Spline);
}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();

    if (!CHECKED(Spline != nullptr, "Spline is nullptr")) return;
}

