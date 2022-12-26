// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemDataTypes.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateDataHealthSignature, const FDataHealth&, DataHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateDataStaminaSignature, const FDataStamina&, DataStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateStatusAbilitySystemSignature, const EStatusAbilitySystem&, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStaminaIsOverSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStaminaIsFullSignature);

UCLASS(ClassGroup = (Managers), HideCategories = ("Variable", "Sockets", "Tags", "ComponentTick", "ComponentReplication", "Activation", "Cooking", "Collision", "AssetUserData"),
    meta = (BlueprintSpawnableComponent))
class PIRATECLICKER_API UAbilitySystemComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this component's properties
    UAbilitySystemComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Action

public:
    /**
     * @public Checked dead owner
     * @return bool
     **/
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsDead() const
    {
        return bDead;
    }

    /**
     * @public Checked Health enabled
     * @return bool
     **/
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsEnableHealth() const
    {
        return bEnableHealth;
    }

    /**
     * @public Checked Stamina enabled
     * @return bool
     **/
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsEnableStamina() const
    {
        return bEnableStamina;
    }

    /**
     * @public Getting constant data health
     * @return FDataHealth
     **/
    UFUNCTION(BlueprintCallable)
    const FDataHealth& GetFreezeDataHealth() const
    {
        return DataHealth;
    }

    /**
     * @public Setup new data ability system
     * @param1 bool bInEnableHealth
     * @param2 FDataHealth& InDataHealth
     * @param3 bool bInEnableStamina
     * @param4 FDataStamina& InDataStamina
     **/
    UFUNCTION(BlueprintCallable)
    void InitAbilityData(const bool bInEnableHealth, const FDataHealth& InDataHealth, const bool bInEnableStamina, const FDataStamina& InDataStamina);

    /**
     * @public Reset data ability system
     **/
    UFUNCTION(BlueprintCallable)
    void ResetAbilityData();

    /**
     * @public Start ability system
     **/
    UFUNCTION(BlueprintCallable)
    void StartAbilitySystem();

    /**
     * @public Start spending stamina
     **/
    UFUNCTION(BlueprintCallable)
    void StartReduceStamina();

    /**
     * @public Stop spending stamina
     **/
    UFUNCTION(BlueprintCallable)
    void StopReduceStamina();

    /**
     * @public Get Status ability system
     **/
    UFUNCTION(BlueprintCallable)
    FORCEINLINE EStatusAbilitySystem GetStatusAbilitySystem() const
    {
        return StatusAbilitySystem;
    }

    /**
     * @public Take damage to Health param
     **/
    UFUNCTION(BlueprintCallable)
    void TakeDamage(const float Damage);

private:
    UFUNCTION()
    void RegisterTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void FillHealth();
    void ReduceStamina();
    void FillStamina();

#pragma endregion

#pragma region DataAbilitySystem

private:
    UPROPERTY(EditAnywhere, Category = "Ability Settings", meta = (DisplayName = "Включить систему здоровья"))
    bool bEnableHealth{true};

    UPROPERTY(EditAnywhere, Category = "Ability Settings", meta = (ToolTip = "Данные по здоровью", EditCondition = "bEnableHealth", EditConditionHides))
    FDataHealth DataHealth;

    UPROPERTY(EditAnywhere, Category = "Ability Settings", meta = (DisplayName = "Включить систему выносливости"))
    bool bEnableStamina{false};

    UPROPERTY(EditAnywhere, Category = "Ability Settings", meta = (ToolTip = "Данные по стамине", EditCondition = "bEnableStamina", EditConditionHides))
    FDataStamina DataStamina;

    bool bDead{false};

    EStatusAbilitySystem StatusAbilitySystem{EStatusAbilitySystem::None};

    FTimerHandle FillStaminaTimerHandle;
    FTimerHandle ReduceStaminaTimerHandle;
    FTimerHandle FillHealthTimerHandle;

#pragma endregion

#pragma region Signature

public:
    UPROPERTY(BlueprintAssignable)
    FUpdateDataHealthSignature OnUpdateDataHealth;

    UPROPERTY(BlueprintAssignable)
    FUpdateDataStaminaSignature OnUpdateDataStamina;

    UPROPERTY(BlueprintAssignable)
    FUpdateStatusAbilitySystemSignature OnUpdateStatusAbilitySystem;

    UPROPERTY(BlueprintAssignable)
    FDeathSignature OnDeath;

    UPROPERTY(BlueprintAssignable)
    FStaminaIsOverSignature OnStaminaIsOver;

    UPROPERTY(BlueprintAssignable)
    FStaminaIsFullSignature OnStaminaIsFull;

private:
    /**
     * @private Change status ability system
     **/
    void ChangeStatusAbilitySystem(const EStatusAbilitySystem& NewStatus);

#pragma endregion
};
