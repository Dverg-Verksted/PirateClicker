#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemDataTypes.generated.h"

UENUM(BlueprintType)
enum class EStatusAbilitySystem : uint8
{
    None,
    Init,
    Reset,
    Run
};

USTRUCT(BlueprintType)
struct FDataHealth
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", DisplayName = "Максимальное здоровье"))
    float MaxHealth{100.0f};
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", DisplayName = "Текущее здоровье"))
    float Health{100.0f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Включить автореген"))
    bool bRegenerateHealth{false};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "На сколько повышать здоровье",
        EditCondition = "bRegenerateHealth", EditConditionHides))
    float UpperHealth{10.0};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "Частота вызова повышения здоровья",
        EditCondition = "bRegenerateHealth", EditConditionHides, ForceUnits = "s"))
    float CallFrequencyUpperHealth{1.0f};

    void Init()
    {
        Health = MaxHealth;
    }

    void CallStepFillHealth()
    {
        Health = FMath::Clamp(Health + UpperHealth, 0.0f, MaxHealth);
    }
    
    void Empty()
    {
        MaxHealth = Health = UpperHealth = CallFrequencyUpperHealth = INDEX_NONE;
        bRegenerateHealth = false;
    }

    FString ToString() const
    {
        return FString::Printf(TEXT("MaxHealth: [%f] | Health: [%f] | bRegenerateHealth: [%i] | UpperHealth: [%f] | CallFrequencyUpperHealth: [%f]"),
            MaxHealth, Health, bRegenerateHealth, UpperHealth, CallFrequencyUpperHealth);
    }
    
    FString ToStringN() const
    {
        return FString::Printf(TEXT("MaxHealth: [%f]\nHealth: [%f]\nbRegenerateHealth: [%i]\nUpperHealth: [%f]\nCallFrequencyUpperHealth: [%f]"),
            MaxHealth, Health, bRegenerateHealth, UpperHealth, CallFrequencyUpperHealth);
    }
};

USTRUCT(BlueprintType)
struct FDataStamina
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", DisplayName = "Максимальная выносливость"))
    float MaxStamina{100.0f};
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", DisplayName = "Текущая выносливость"))
    float Stamina{100.0f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "На сколько тратить выносливость"))
    float ReduceStamina{5.0f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "Частота вызова траты выносливости", ForceUnits = "s"))
    float CallFrequencyReduceStamina{1.0f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Включить автовостановление выносливости"))
    bool bRegenerateStamina{true};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "На сколько повышать выносливость",
        EditCondition = "bRegenerateStamina", EditConditionHides))
    float UpperStamina{10.0};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", DisplayName = "Частота вызова повышения выносливости",
        EditCondition = "bRegenerateStamina", EditConditionHides, ForceUnits = "s"))
    float CallFrequencyUpperStamina{1.0f};

    void Init()
    {
        Stamina = MaxStamina;
    }

    void CallStepFillStamina()
    {
        Stamina = FMath::Clamp(Stamina + UpperStamina, 0.0f, MaxStamina);
    }

    void CallStepReduceStamina()
    {
        Stamina = FMath::Clamp(Stamina - ReduceStamina, 0.0f, MaxStamina);
    }

    void Empty()
    {
        MaxStamina = Stamina = UpperStamina = CallFrequencyUpperStamina = INDEX_NONE;
        bRegenerateStamina = false;
    }

    FString ToString() const
    {
        return FString::Printf(TEXT("MaxStamina: [%f] | Stamina: [%f] | bRegenerateStamina: [%i] | UpperStamina: [%f] | CallFrequencyUpperStamina: [%f]"),
            MaxStamina, Stamina, bRegenerateStamina, UpperStamina, CallFrequencyUpperStamina);
    }

    FString ToStringN() const
    {
        return FString::Printf(TEXT("MaxStamina: [%f]\nStamina: [%f]\nbRegenerateStamina: [%i]\nUpperStamina: [%f]\nCallFrequencyUpperStamina: [%f]"),
            MaxStamina, Stamina, bRegenerateStamina, UpperStamina, CallFrequencyUpperStamina);
    }

    bool IsStaminaFull() const
    {
        return Stamina == MaxStamina;
    }
};
