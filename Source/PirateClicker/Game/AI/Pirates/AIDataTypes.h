#pragma once

#include "AIDataTypes.generated.h"

#define M_TO_CM 100.0f

// A special state for pirate
UENUM()
enum class EStateBrain : uint8
{
    Idle UMETA(DisplayName = "Стоит"),
    Walk UMETA(DisplayName = "Идет"),
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

    bool IsValid() const
    {
        return  this->StartPointPosition != FVector::ZeroVector &&
                this->EndPointPosition != FVector::ZeroVector &&
                this->TimeMoveDelta == 0.0f &&
                this->StartRotatePosition != FRotator::ZeroRotator &&
                this->EndRotatePosition != FRotator::ZeroRotator &&
                this->TimeRotateDelta == 0.0f;
    }
};
