// This section is the property of the Dverg Verksted team

#include "Game/AI/Pirates/PirateActorBase.h"
#include "MovePirateComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/AI/Spawner/SplineActor.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

// Sets default values
APirateActorBase::APirateActorBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

    CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule collision"));
    SetRootComponent(CapsuleCollision);

    PirateMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Skeletal mesh"));
    PirateMesh->SetupAttachment(CapsuleCollision);

    MovePirateComponent = CreateDefaultSubobject<UMovePirateComponent>(FName("Movement component"));
}

void APirateActorBase::InitParamsPirate(const FDataPirate& DataPirate, ASplineActor* NewSpline)
{
    if (!CHECKED(StateBrain == EStateBrain::NoneInit, "Pirate is init!")) return;

    MovePirateComponent->InitMoveData(DataPirate.SpeedMove, DataPirate.SpeedRotate);
    SetupTargetSpline(NewSpline);
}

// Called when the game starts or when spawned
void APirateActorBase::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(CapsuleCollision != nullptr, "Capsule collision is nullptr")) return;
    if (!CHECKED(PirateMesh != nullptr, "Skeletal mesh is nullptr")) return;
    if (!CHECKED(MovePirateComponent != nullptr, "Movement pirate component is nullptr")) return;
    if (!CHECKED(TargetSpline != nullptr, "Target spline is nullptr")) return;
    if (!CHECKED(TargetSpline->GetSpline() != nullptr, "Spline is nullptr")) return;

    MovePirateComponent->OnStopedMove.AddDynamic(this, &ThisClass::NextMoveToPoint);
    StateBrain = EStateBrain::WalkToStorage;
    NextMoveToPoint();
}

#pragma endregion

#pragma region Action

void APirateActorBase::SetupTargetSpline(ASplineActor* NewSpline)
{
    if (!CHECKED(NewSpline != nullptr, "New Spline is nullptr")) return;

    TargetSpline = NewSpline;
}

void APirateActorBase::SetupStateBrain(const EStateBrain& NewState)
{
    if (!CHECKED(StateBrain != NewState, "Current state brain == New State")) return;

    LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("New brain state: [%s]"),
        *UEnum::GetValueAsString(NewState)));
    StateBrain = NewState;
}

void APirateActorBase::NextMoveToPoint()
{
    if (!CHECKED(StateBrain != EStateBrain::Idle, "State brain equal idle")) return;

    LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("Current state brain: [%s]"),
        *UEnum::GetValueAsString(StateBrain)));
    if (StateBrain == EStateBrain::WalkToStorage)
    {
        TargetIndex++;
        const FVector NewPos = TargetSpline->GetSpline()->GetLocationAtSplinePoint(TargetIndex, ESplineCoordinateSpace::World);
        LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("New position [%s] from spline: [%s]"),
            *NewPos.ToString(), *TargetSpline->GetName()));
        MovePirateComponent->GoAIMove(NewPos);
    }

    if (StateBrain == EStateBrain::WalkToBack)
    {
        TargetIndex--;
    }
}

#pragma endregion