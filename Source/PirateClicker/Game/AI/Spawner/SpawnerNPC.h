// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerNPC.generated.h"

class USphereComponent;

UCLASS()
class PIRATECLICKER_API ASpawnerNPC : public AActor
{
    GENERATED_BODY()

#pragma region Default
    
public:
    // Sets default values for this actor's properties
    ASpawnerNPC();

    /** 
     *	Function called every frame on this Actor. Override this function to implement custom logic to be executed every frame.
     *	Note that Tick is disabled by default, and you will need to check PrimaryActorTick.bCanEverTick is set to true to enable it.
     *
     *	@param	DeltaSeconds	Game time elapsed during last frame modified by the time dilation
     */
    virtual void Tick(float DeltaSeconds) override;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:

    // @protected Root scene component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // @protected Billboard component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBillboardComponent* Billboard;

    // @protected Sphere Collision
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereCollision;

#pragma endregion
    
};
