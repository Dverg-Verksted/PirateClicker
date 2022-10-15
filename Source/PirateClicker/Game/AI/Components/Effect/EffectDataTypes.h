#pragma once

#include "CoreMinimal.h"
#include "EffectDataTypes.generated.h"

UENUM()
enum class ETypeEffect : uint8
{
    Fire,
    Cold,
};

USTRUCT(BlueprintType)
struct FDataEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Тип эффекта"))
    ETypeEffect TypeEffect{ETypeEffect::Fire};

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Наносимый дамаг", ClampMin = "0.01", EditCondition = "TypeEffect == ETypeEffect::Fire", EditConditionHides))
    float Damage{1.0f};

    UPROPERTY(EditAnywhere, meta = (DisplayName = "Скорость замедления", ClampMin = "1.0", ClampMax = "100.0", ForceUnits = "%", EditCondition = "TypeEffect == ETypeEffect::Cold", EditConditionHides))
    float SpeedConversion{10.0f};

    FString ToString() const { return FString::Printf(TEXT("Type effect: [%s] | Damage: [%f] | SpeedConversion: [%f]"), *UEnum::GetValueAsString(TypeEffect), Damage, SpeedConversion); }
};
