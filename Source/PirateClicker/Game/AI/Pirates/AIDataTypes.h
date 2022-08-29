#pragma once

#include "AIDataTypes.generated.h"

#define M_TO_CM 100.0f

UENUM()
enum class EStateMovement : uint8
{
    Off,
    Rotating,
    Moving
};

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

    // Vector of the starting point
    FVector StartPointPosition{FVector::ZeroVector};

    // Vector of the final position for movement
    FVector EndPointPosition{FVector::ZeroVector};

    // Intermediate value for time travel
    float TimeMoveDelta{0.0f};

    // Vector of the starting point
    FRotator StartRotatePosition{FRotator::ZeroRotator};

    // Vector of the final position for movement
    FRotator EndRotatePosition{FRotator::ZeroRotator};

    // Intermediate value for Rotate travel
    float TimeRotateDelta{0.0f};

    bool IsValid() const { return this->StartPointPosition != FVector::ZeroVector && this->EndPointPosition != FVector::ZeroVector && this->TimeMoveDelta == 0.0f && this->TimeRotateDelta == 0.0f; }
};
