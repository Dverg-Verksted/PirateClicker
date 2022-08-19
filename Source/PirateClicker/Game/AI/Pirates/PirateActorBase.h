// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AIDataTypes.h"
#include "GameFramework/Actor.h"
#include "PirateActorBase.generated.h"

class ASplineActor;
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
    UMovePirateComponent* MovePirateComponent{nullptr};

#pragma endregion

#pragma region DataPirate

protected:
    
    // @protected Target spline
    UPROPERTY()
    ASplineActor* TargetSpline;

    // @protected Current state brain
    EStateBrain StateBrain = EStateBrain::Idle;

    int32 TargetIndex = -1;

#pragma endregion

#pragma region Action
    
public:

    /**
     * @public Change target spline for pirate
     * @param1 ASplineMeshActor*
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Action")
    void SetupTargetSpline(ASplineActor* NewSpline);

    /**
     * @public Setup new state brain
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Action")
    void SetupStateBrain(const EStateBrain& NewState);

private:

    /**
     * @private Next Move To Point
     **/
    UFUNCTION()
    void NextMoveToPoint();

#pragma endregion
};
