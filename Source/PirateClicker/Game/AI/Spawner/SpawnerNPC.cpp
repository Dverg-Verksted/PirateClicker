// This section is the property of the Dverg Verksted team

#include "Game/AI/Spawner/SpawnerNPC.h"

// Sets default values
ASpawnerNPC::ASpawnerNPC()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnerNPC::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASpawnerNPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
