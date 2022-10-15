// This section is the property of the Dverg Verksted team

#include "Game/AI/Components/MovePirateComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"
#include "Game/AI/Spawner/SplineActor.h"
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

    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;
}

void UMovePirateComponent::Print_LogMovement(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function) const
{
    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;

    UPirateClickerLibrary::Print_Log(LogVerb, FString::Printf(TEXT("Name: [%s] | State movement: [%s] | %s"), *GetOwner()->GetName(), *UEnum::GetValueAsString(StateMovement), *Text), Line, Function);
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

    if (StateMovement == EStateMovement::ForSpline)
    {
        MoveToSpline(DeltaTime);
    }
}

void UMovePirateComponent::InitMoveData(const float SpeedMove, const float SpeedRotate)
{
    DefaultSpeedMove = SpeedMove;
    DefaultSpeedRotate = SpeedRotate;
}

#pragma endregion

#pragma region DataMove

void UMovePirateComponent::GoAIMoveAdvance(const FVector& ToPos, ASplineActor* SplineActor, const float Duration, bool const bReverse)
{
    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;

    FMovementData MovementData;
    MovementData.StartPointPosition = GetOwner()->GetActorLocation();
    MovementData.EndPointPosition = ToPos;
    MovementData.StartRotatePosition = GetOwner()->GetActorRotation();
    FVector StartPoint = GetOwner()->GetActorLocation();
    StartPoint.Z = 0.0f;
    FVector EndPoint = ToPos;
    EndPoint.Z = 0.0f;
    MovementData.EndRotatePosition = (EndPoint - StartPoint).Rotation();
    MovementData.TargetSpline = SplineActor;
    MovementData.Duration = Duration;
    MovementData.bReverse = bReverse;
    RunMovement(MovementData);
}

void UMovePirateComponent::GoAIMove(const FVector& ToPos)
{
    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;

    FMovementData MovementData;
    MovementData.StartPointPosition = GetOwner()->GetActorLocation();
    MovementData.EndPointPosition = ToPos;
    MovementData.StartRotatePosition = GetOwner()->GetActorRotation();
    FVector StartPoint = GetOwner()->GetActorLocation();
    StartPoint.Z = 0.0f;
    FVector EndPoint = ToPos;
    EndPoint.Z = 0.0f;
    MovementData.EndRotatePosition = (EndPoint - StartPoint).Rotation();
    RunMovement(MovementData);
}

bool UMovePirateComponent::RunMovement(const FMovementData& NewData)
{
    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return false;
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
        GetOwner()->SetActorLocation(NewPointLocation);
        TargetData.TimeMoveDelta += DeltaTime;
    }
    else
    {
        if (TargetData.TargetSpline)
        {
            StateMovement = EStateMovement::ForSpline;
        }
        else
        {
            StopMovement();
        }
    }
}

void UMovePirateComponent::CalculateRotate(float DeltaTime)
{
    if (TargetData.TimeRotateDelta < EndTime)
    {
        const FRotator NewRotate = FMath::Lerp(TargetData.StartRotatePosition, TargetData.EndRotatePosition, TargetData.TimeRotateDelta / EndTime);
        GetOwner()->SetActorRotation(NewRotate);
        TargetData.TimeRotateDelta += DeltaTime;
    }
    else
    {
        GetOwner()->SetActorRotation(TargetData.EndRotatePosition);
        EndTime = (TargetData.EndPointPosition - TargetData.StartPointPosition).Size() / (DefaultSpeedMove * M_TO_CM);
        StateMovement = EStateMovement::Moving;
    }
}

void UMovePirateComponent::MoveToSpline(float DeltaTime)
{
    const FVector TempPos = TargetData.TargetSpline->GetSpline()->GetLocationAtTime(TargetData.Duration, ESplineCoordinateSpace::World, true);
    const FRotator TempRot = ((TempPos - GetOwner()->GetActorLocation()).GetSafeNormal()).Rotation();
    GetOwner()->SetActorLocation(TempPos);
    GetOwner()->SetActorRotation(TempRot);
    TargetData.Duration = TargetData.bReverse ? TargetData.Duration - ((DefaultSpeedMove / M_TO_CM) * DeltaTime) : TargetData.Duration + ((DefaultSpeedMove / M_TO_CM) * DeltaTime);
    if (TargetData.bReverse && TargetData.Duration <= 0.0f)
    {
        StopMovement();
    }

    if (!TargetData.bReverse && TargetData.Duration >= 1.0f)
    {
        StopMovement();
    }

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_MovementPirate.GetValueOnGameThread())
    {
        LOG_MOVE(ELogVerb::Display, FString::Printf(TEXT("New pos: [%s] | New rot: [%s] | Duration: [%f]"), *TempPos.ToString(), *TempRot.ToString(), TargetData.Duration));
    }
#endif
}

#pragma endregion
