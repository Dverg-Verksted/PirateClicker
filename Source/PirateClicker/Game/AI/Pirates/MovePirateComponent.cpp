// This section is the property of the Dverg Verksted team


#include "Game/AI/Pirates/MovePirateComponent.h"

#include "Library/PirateClickerLibrary.h"

#pragma region Default

// Sets default values for this component's properties
UMovePirateComponent::UMovePirateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
    PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

    
}

// Called when the game starts
void UMovePirateComponent::BeginPlay()
{
	Super::BeginPlay();
    
	OwnerPirate = GetOwner();
    if (!CHECKED(OwnerPirate != nullptr, ""))
}

// Called every frame
void UMovePirateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bEnableMove)
    {
        CalculateMove();
        CalculateRotate();
    }
}

#pragma endregion


#pragma region DataMove

bool UMovePirateComponent::StartMove(const FMovementData& NewData)
{
    if (!CHECKED(OwnerPirate != nullptr, "Owner pirate is nullptr")) return false;
    if (!CHECKED(TargetSpline != nullptr, "Target spline is nullptr")) return false;
    if (!CHECKED(NewData.IsValid() != false, "Target position is not valid")) return false;

    TargetData = NewData;
    
    
    return true;
}

void UMovePirateComponent::CalculateMove()
{
    // if (this->TimeMoveEylips < Distance / DefaultSpeedMove)
    // {
    //     const FVector NewPointLocation =
    //         FMath::Lerp(this->StartPointPosition, this->EndPointPosition, this->TimeMoveEylips / this->TimeMove);
    //     SetActorLocation(NewPointLocation);
    //     this->TimeMoveEylips += DeltaTime;
    // }
    // else
    // {
    //     SetActorLocation(this->EndPointPosition);
    //     if (this->StateBrain == EStateBrain::Walk) this->StateBrain = EStateBrain::Idle;
    //     this->StopMovement();
    // }
}

void UMovePirateComponent::CalculateRotate()
{
    
}

#pragma endregion
