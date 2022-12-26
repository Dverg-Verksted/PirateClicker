#pragma once

#include "Spawner/SplineActor.h"
#include "AIDataTypes.generated.h"

#define M_TO_CM 100.0f

UENUM()
enum class EStateMovement : uint8
{
    Stop,
    Move,
    Pause,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeMovementStateSignature, const EStateMovement&, StateMovement);

// A special state for pirate
UENUM()
enum class EStateBrain : uint8
{
    NoneInit UMETA(DisplayName = "Не иницилизированный пират"),
    Idle UMETA(DisplayName = "Стоит"),
    WalkToStorage UMETA(DisplayName = "Идет до золота"),
    WalkToBack UMETA(DisplayName = "Идет обратно"),
    WaitFor UMETA(DisplayName = "Отдыхает"),
};

USTRUCT()
struct FMovementData
{
    GENERATED_BODY()

    float Duration{0.0f};
    bool bReverse{false};

    UPROPERTY()
    ASplineActor* TargetSpline{nullptr};

    FMovementData() {}
    explicit FMovementData(const float InDuration, const bool InReverse, ASplineActor* InTargetSpline) : Duration(InDuration), bReverse(InReverse), TargetSpline(InTargetSpline) {}

    FString ToString() const { return FString::Printf(TEXT("Duration: [%f] | bReverse: [%i] | TargetSpline: [%s]"), Duration, bReverse, *TargetSpline->GetName()); }

    FString ToStringN() const { return FString::Printf(TEXT("Duration: [%f]\nbReverse: [%i]\nTargetSpline: [%s]"), Duration, bReverse, *TargetSpline->GetName()); }
};
