// This section is the property of the Dverg Verksted team

#include "Game/AI/Components/MoveComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
static TAutoConsoleVariable<bool> EnableD_MovementPirate(TEXT("Pirate.ShowMove"), false, TEXT("Enable debug information about the movement of pirates"), ECVF_Cheat);
#endif

#pragma region Default

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
    PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

// Called when the game starts
void UMoveComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;
}

void UMoveComponent::Print_LogMovement(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function) const
{
    if (!CHECKED(GetOwner() != nullptr, "Owner pirate is nullptr")) return;

    UPirateClickerLibrary::Print_Log(LogVerb, FString::Printf(TEXT("Name: [%s] | State movement: [%s] | %s"), *GetOwner()->GetName(), *UEnum::GetValueAsString(StateMovement), *Text), Line, Function);
}

// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
    if (EnableD_MovementPirate.GetValueOnGameThread() && GetOwner())
    {
        DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), TargetData.ToStringN(), nullptr, FColor::Orange, 0.0f, false, 1.0f);
    }
#endif

    if (StateMovement == EStateMovement::Move)
    {
        MoveToSpline(DeltaTime);
    }
}

void UMoveComponent::InitMoveData(const float SpeedMove, const float SpeedRotate)
{
    DefaultSpeedMove = SpeedMove;
    DefaultSpeedRotate = SpeedRotate;
}

#pragma endregion

#pragma region Action

void UMoveComponent::GoMove(const FMovementData& MovementData)
{
    StopMovement();
    LOG_MOVE(ELogVerb::Display, FString::Printf(TEXT("Movement Data: [%s]"), *MovementData.ToString()));
    TargetData = MovementData;
    ChangeMovementState(EStateMovement::Move);
}

#pragma endregion

#pragma region DataMove

void UMoveComponent::StopMovement()
{
    ChangeMovementState(EStateMovement::Stop);
}

void UMoveComponent::SetupSpeedModifyToPercent(const float SpeedPercent)
{
    SpeedModify = FMath::Clamp(SpeedPercent, 0.0f, 1.0f);
}

void UMoveComponent::ResetSpeedModifyToPercent()
{
    SpeedModify = 1.0f;
}

void UMoveComponent::PauseMove()
{
    if (StateMovement == EStateMovement::Move)
    {
        ChangeMovementState(EStateMovement::Pause);
    }
}

void UMoveComponent::ResumeMove()
{
    if (StateMovement == EStateMovement::Pause)
    {
        ChangeMovementState(EStateMovement::Move);
    }
}

void UMoveComponent::ChangeMovementState(const EStateMovement& NewState)
{
    if (!CHECKED(StateMovement != NewState, "State movement equal new state")) return;

    StateMovement = NewState;
    OnChangeMovementState.Broadcast(NewState);
}

void UMoveComponent::MoveToSpline(float DeltaTime)
{
    const FVector TempPos = TargetData.TargetSpline->GetSpline()->GetLocationAtTime(TargetData.Duration, ESplineCoordinateSpace::World, true);
    const FRotator TempRot = ((TempPos - GetOwner()->GetActorLocation()).GetSafeNormal()).Rotation();
    GetOwner()->SetActorLocation(TempPos);
    GetOwner()->SetActorRotation(TempRot);
    TargetData.Duration = TargetData.bReverse ? TargetData.Duration - (((DefaultSpeedMove * SpeedModify) / M_TO_CM) * DeltaTime) : TargetData.Duration + (((DefaultSpeedMove * SpeedModify) / M_TO_CM) * DeltaTime);
    if (TargetData.bReverse && TargetData.Duration <= 0.0f)
    {
        StopMovement();
    }

    if (!TargetData.bReverse && TargetData.Duration >= 1.0f)
    {
        StopMovement();
    }

#if UE_EDITOR || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
    if (EnableD_MovementPirate.GetValueOnGameThread())
    {
        LOG_MOVE(ELogVerb::Display, FString::Printf(TEXT("New pos: [%s] | New rot: [%s] | Duration: [%f]"), *TempPos.ToString(), *TempRot.ToString(), TargetData.Duration));
    }
#endif
}

#pragma endregion
