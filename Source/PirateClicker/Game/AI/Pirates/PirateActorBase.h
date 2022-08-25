// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AIDataTypes.h"
#include "Game/AI/DataAsset/PirateDataAsset.h"
#include "GameFramework/Actor.h"
#include "PirateActorBase.generated.h"

class UHealthComponent;
class ASplineActor;
class UMovePirateComponent;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPirateDeadSignature, APirateActorBase*, Pirate);

UCLASS()
class PIRATECLICKER_API APirateActorBase : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    
    // Sets default values for this actor's properties
    APirateActorBase();

    /**
     * @public Initializing parameters for a pirate
     * @param1 FDataPirate
     * @param2 ASplineActor
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Default")
    void InitParamsPirate(const FDataPirate& DataPirate, ASplineActor* NewSpline);

protected:
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

public:

    /**
     * @public Get capsule collision
     * @return UCapsuleComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Components")
    UCapsuleComponent* GetCapsuleCollision() const { return CapsuleCollision; }

    /**
     * @public Get pirate mesh
     * @return USkeletalMeshComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Components")
    USkeletalMeshComponent* GetPirateMesh() const { return PirateMesh; }

    /**
     * @public Get move pirate component
     * @return UMovePirateComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Components")
    UMovePirateComponent* GetMovePirateComponent() const { return MovePirateComponent; }

    /**
     * @public Get health component
     * @return UHealthComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Components")
    UHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
    
    // @protected Root capsule collision
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UCapsuleComponent* CapsuleCollision{nullptr};

    // @protected Pirate skeletal mesh component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USkeletalMeshComponent* PirateMesh{nullptr};

    // @protected actor component for custom movement
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMovePirateComponent* MovePirateComponent{nullptr};

    // @protected actor component for health pirate
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UHealthComponent* HealthComponent{nullptr};

#pragma endregion

#pragma region DataPirate

protected:
    
    // @protected Target spline
    UPROPERTY()
    ASplineActor* TargetSpline;

    // @protected Current state brain
    EStateBrain StateBrain = EStateBrain::NoneInit;

    int32 TargetIndex = -1;

#pragma endregion

#pragma region Action
    
public:
    
    /**
     * @public Change target spline for pirate
     * @param1 ASplineActor*
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
     * @private Register hit on actor
     * @param1 AActor*
     **/
    UFUNCTION()
    void RegisterHitActor(AActor* HitActor);
    
    /**
     * @private Next Move To Point
     **/
    UFUNCTION()
    void NextMoveToPoint();

#pragma endregion

#pragma region Signature

public:

    // @public Signature on the death of a pirate
    UPROPERTY(BlueprintAssignable)
    FPirateDeadSignature OnPirateDead;

#pragma endregion
};
