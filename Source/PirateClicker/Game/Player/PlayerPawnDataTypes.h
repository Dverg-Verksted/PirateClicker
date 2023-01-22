#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnDataTypes.generated.h"


UENUM(BlueprintType)
enum class ECameraPawnMoved: uint8
{
    InPlace UMETA(DisplayName = "На месте"),
    OnLeft UMETA(DisplayName = "Налево"),
    OnRight UMETA(DisplayName = "Направо"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateCameraPawnMovedSignature, ECameraPawnMoved, State);

USTRUCT(BlueprintType)
struct FDataInfoBound
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector WorldPosition{FVector::ZeroVector};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float Distance{0.0f};
};
