// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PirateActorBase.generated.h"

class UMovePirateComponent;
class UCapsuleComponent;

UCLASS()
class PIRATECLICKER_API APirateActorBase : public AActor
{
	GENERATED_BODY()

#pragma region Default
    
public:	
	// Sets default values for this actor's properties
	APirateActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:

    // Root capsule collision
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* CapsuleCollision{nullptr};
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* PirateMesh{nullptr};
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMovePirateComponent* MovePirateComponent;

#pragma endregion

};
