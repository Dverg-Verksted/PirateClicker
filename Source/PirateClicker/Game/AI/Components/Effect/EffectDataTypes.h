#pragma once

#include "CoreMinimal.h"
#include "EffectDataTypes.generated.h"

UENUM()
enum class ETypeEffect : uint8
{
    None,
    PhysicalDamage,
    SlowingDown,
};

USTRUCT(BlueprintType)
struct FDataEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Тип эффекта"))
    ETypeEffect TypeEffect{ETypeEffect::None};

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Наносимый дамаг", ClampMin = "0.01", EditCondition = "TypeEffect == ETypeEffect::PhysicalDamage", EditConditionHides))
    float Damage{1.0f};

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Скорость замедления", ClampMin = "0.1", ClampMax = "1.0", ForceUnits = "x", EditCondition = "TypeEffect == ETypeEffect::SlowingDown", EditConditionHides))
    float SpeedConversion{0.5f};

    FString ToString() const { return FString::Printf(TEXT("Type effect: [%s] | Damage: [%f] | SpeedConversion: [%f]"), *UEnum::GetValueAsString(TypeEffect), Damage, SpeedConversion); }
};
