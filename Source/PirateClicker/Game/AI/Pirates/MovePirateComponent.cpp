// This section is the property of the Dverg Verksted team

#include "Game/AI/Pirates/MovePirateComponent.h"
#include "DrawDebugHelpers.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_MovementPirate(TEXT("Pirate.ShowDebugMovementPirate"), false, TEXT("Enable debag information about the movement of pirates"), ECVF_Cheat);
#endif

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
    if (!CHECKED(OwnerPirate != nullptr, "Owner pirate is nullptr")) return;
}

void UMovePirateComponent::Print_LogMovement(const ELogRSVerb LogVerb, const FString Text, const int Line, const char* Function) const
{
    if (!CHECKED(OwnerPirate != nullptr, "Owner pirate is nullptr")) return;

    UPirateClickerLibrary::Print_Log(LogVerb, FString::Printf(TEXT("Name: [%s] | State movement: [%s] | %s"), *OwnerPirate->GetName(), *UEnum::GetValueAsString(StateMovement), *Text), Line, Function);
}

// Called every frame
void UMovePirateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_MovementPirate.GetValueOnGameThread())
    {
        DrawDebugSphere(GetWorld(), TargetData.StartPointPosition, 12.0f, 12, FColor::Blue, false, 0.0f, 0, 2.0f);
        DrawDebugSphere(GetWorld(), TargetData.EndPointPosition, 12.0f, 12, FColor::Blue, false, 0.0f, 0, 2.0f);
        DrawDebugLine(GetWorld(), TargetData.StartPointPosition, TargetData.EndPointPosition, FColor::Cyan, false, 0.0f, 0, 2.0f);
    }
#endif

    if (StateMovement == EStateMovement::Moving)
    {
        CalculateMove(DeltaTime);
    }

    if (StateMovement == EStateMovement::Rotating)
    {
        CalculateRotate(DeltaTime);
    }
}

void UMovePirateComponent::InitMoveData(const float SpeedMove, const float SpeedRotate)
{
    DefaultSpeedMove = SpeedMove;
    DefaultSpeedRotate = SpeedRotate;
}

#pragma endregion

#pragma region DataMove

void UMovePirateComponent::GoAIMove(const FVector& ToPos)
{
    if (!CHECKED(OwnerPirate != nullptr, "Owner pirate is nullptr")) return;

    FMovementData MovementData;
    MovementData.StartPointPosition = OwnerPirate->GetActorLocation();
    MovementData.EndPointPosition = ToPos;
    MovementData.StartRotatePosition = OwnerPirate->GetActorRotation();
    FVector StartPoint = OwnerPirate->GetActorLocation();
    StartPoint.Z = 0.0f;
    FVector EndPoint = ToPos;
    EndPoint.Z = 0.0f;
    MovementData.EndRotatePosition = (EndPoint - StartPoint).Rotation();
    RunMovement(MovementData);
}

bool UMovePirateComponent::RunMovement(const FMovementData& NewData)
{
    if (!CHECKED(OwnerPirate != nullptr, "Owner pirate is nullptr")) return false;
    if (!CHECKED(NewData.IsValid() != false, "Target position is not valid")) return false;

    TargetData = NewData;
    EndTime = (TargetData.EndRotatePosition.Vector() - TargetData.StartRotatePosition.Vector()).Size() / DefaultSpeedRotate;
    StateMovement = EStateMovement::Rotating;

    return true;
}

void UMovePirateComponent::StopMovement()
{
    StateMovement = EStateMovement::Off;
    OnStopedMove.Broadcast();
}

void UMovePirateComponent::CalculateMove(float DeltaTime)
{
    if (TargetData.TimeMoveDelta < EndTime)
    {
        const FVector NewPointLocation = FMath::Lerp(TargetData.StartPointPosition, TargetData.EndPointPosition, TargetData.TimeMoveDelta / EndTime);
        OwnerPirate->SetActorLocation(NewPointLocation);
        TargetData.TimeMoveDelta += DeltaTime;
    }
    else
    {
        StopMovement();
    }
}

void UMovePirateComponent::CalculateRotate(float DeltaTime)
{
    if (TargetData.TimeRotateDelta < EndTime)
    {
        const FRotator NewRotate = FMath::Lerp(TargetData.StartRotatePosition, TargetData.EndRotatePosition, TargetData.TimeRotateDelta / EndTime);
        OwnerPirate->SetActorRotation(NewRotate);
        TargetData.TimeRotateDelta += DeltaTime;
    }
    else
    {
        OwnerPirate->SetActorRotation(TargetData.EndRotatePosition);
        EndTime = (TargetData.EndPointPosition - TargetData.StartPointPosition).Size() / (DefaultSpeedMove * M_TO_CM);
        StateMovement = EStateMovement::Moving;
    }
}

#pragma endregion
