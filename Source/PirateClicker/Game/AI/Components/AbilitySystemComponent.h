// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdateSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);

UCLASS(ClassGroup = (Managers), HideCategories = ("Variable", "Sockets", "Tags", "ComponentTick", "ComponentReplication", "Activation", "Cooking", "Collision", "AssetUserData"),
    meta = (BlueprintSpawnableComponent))
class PIRATECLICKER_API UAbilitySystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAbilitySystemComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

#pragma region Health

public:
    UFUNCTION(BlueprintCallable, Category = "Damage and Health", meta = (ToolTip = "Дай мне свой урон"))
    void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable, Category = "Damage and Health", meta = (ToolTip = "Функция для получения текущего хп актера"))
    FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintCallable, Category = "Damage and Health", meta = (ToolTip = " Функция для получения максимального хп актера"))
    FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Damage and Health", meta = (ToolTip = "Функция для изменения максимального хп актера"))
    void SetMaxHealth(const float HealthToSet) { MaxHealth = HealthToSet; }

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return bDead; }

    UPROPERTY(BlueprintAssignable)
    FHealthUpdateSignature OnUpdateHealth;

    UPROPERTY(BlueprintAssignable)
    FDeathSignature OnDeath;

private:
    UPROPERTY(EditAnywhere, Category = "Health Settings", meta = (DisplayName = "Включить систему здоровья"))
    bool bEnableHealth = true;

    UPROPERTY(EditAnywhere, Category = "Health Settings",
        meta = (ClampMin = "0", ToolTip = "Здесь можно изменять максимальное хп актера с этим компонентом", EditCondition = "bEnableHealth", EditConditionHides))
    float MaxHealth = 100;

    float CurrentHealth = 0;
    bool bDead{false};

#pragma endregion
};
