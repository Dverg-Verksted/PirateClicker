// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerNPC.generated.h"

UCLASS()
class PIRATECLICKER_API ASpawnerNPC : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpawnerNPC();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
