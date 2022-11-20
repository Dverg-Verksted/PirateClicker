// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Game/AI/AIDataTypes.h"
#include "Game/AI/DataAsset/PirateDataAsset.h"
#include "GameFramework/Actor.h"
#include "PirateActorBase.generated.h"

class UMoveComponent;
class AGoldStorageActor;
class AGoldChest;
class UEffectManager;
class UAbilitySystemComponent;
class ASplineActor;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPirateDeadSignature, APirateActorBase*, Pirate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusTreasureSignature, bool, bHaveTreasure);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateBrainSignature, const EStateBrain&, StateBrain);

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
    UMoveComponent* GetMovePirateComponent() const { return MoveComponent; }

    /**
     * @public Get ability component
     * @return UMovePirateComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Components")
    UAbilitySystemComponent* GetAbilityComponent() const { return AbilitySystem; }

protected:
    // @protected Root capsule collision
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UCapsuleComponent* CapsuleCollision{nullptr};

    // @protected Pirate skeletal mesh component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USkeletalMeshComponent* PirateMesh{nullptr};

    // @protected actor component for custom movement
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMoveComponent* MoveComponent{nullptr};

    // @protected actor component for health pirate
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UAbilitySystemComponent* AbilitySystem;

    // @protected actor component for health pirate
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UEffectManager* EffectManager;

#pragma endregion

#pragma region DataPirate

public:
    bool bHasTreasure{false};

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Settings Pirate")
    UAnimMontage* DeadMontage{nullptr};

    // @protected Target spline
    UPROPERTY()
    ASplineActor* TargetSpline;

    // @protected Current state brain
    EStateBrain StateBrain = EStateBrain::NoneInit;

    // @protected Current state brain
    EStateBrain LastStateBrain = EStateBrain::NoneInit;

    int32 TargetIndex = -1;

private:
    UPROPERTY()
    AGoldChest* GoldChest;

    UPROPERTY()
    AGoldStorageActor* GoldStorageFrom{nullptr};

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
    void SetupStateBrain(const EStateBrain NewState);

    /**
     * @public Getting state brain
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Action")
    EStateBrain GetStateBrain() const { return StateBrain; }

    /**
     * @public Register death
     **/
    UFUNCTION()
    void RegisterDeadActor();

    UFUNCTION()
    void SpawnGoldChest(const TSubclassOf<AGoldChest>& SubClassGoldChest, AGoldStorageActor* GoldStorageActor);

    UFUNCTION()
    float PlayMontage(UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) const;

private:

    /**
     * @private Move To Point
     **/
    UFUNCTION()
    void MoveToPoint() const;

    UFUNCTION()
    void BackChestToStorage();

    /**
     * @private 
     **/
    UFUNCTION()
    void RegisterStaminaOver();
    
    /**
     * @private 
     **/
    UFUNCTION()
    void RegisterStaminaFull();

#pragma endregion

#pragma region Signature

public:
    // @public Signature on the death of a pirate
    UPROPERTY(BlueprintAssignable)
    FPirateDeadSignature OnPirateDead;

    // @public notify change status treasure
    UPROPERTY(BlueprintAssignable)
    FStatusTreasureSignature OnStatusTreasure;

    // @public notify change status treasure
    UPROPERTY(BlueprintAssignable)
    FChangeStateBrainSignature OnChangeStateBrain;

#pragma endregion
};
