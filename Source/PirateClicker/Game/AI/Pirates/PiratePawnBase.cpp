// This section is the property of the Dverg Verksted team


#include "Game/AI/Pirates/PiratePawnBase.h"

// Sets default values
APiratePawnBase::APiratePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

// Called when the game starts or when spawned
void APiratePawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}


