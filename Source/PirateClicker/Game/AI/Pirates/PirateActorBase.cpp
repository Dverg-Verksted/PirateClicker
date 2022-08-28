// This section is the property of the Dverg Verksted team

#include "Game/AI/Pirates/PirateActorBase.h"
#include "AbilitySystemComponent.h"
#include "MovePirateComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Game/AI/Spawner/SplineActor.h"
#include "Game/Player/GamePC.h"
#include "Kismet/GameplayStatics.h"
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
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(FName("Ability system component"));
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
    if (!CHECKED(AbilitySystem != nullptr, "AbilitySystem is nullptr")) return;
    AbilitySystem->OnDeath.AddDynamic(this, &ThisClass::RegisterDeadActor);

    AGamePC* GamePC = Cast<AGamePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!CHECKED(GamePC != nullptr, "Game player controller is nullptr")) return;

    GamePC->OnHitActor.AddDynamic(this, &ThisClass::RegisterHitActor);
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

    LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("New brain state: [%s]"), *UEnum::GetValueAsString(NewState)));
    StateBrain = NewState;
}

void APirateActorBase::RegisterHitActor(AActor* HitActor)
{
    if (this == HitActor && AbilitySystem)
    {
        AbilitySystem->TakeDamage(HitActor, 10.0f, nullptr, nullptr, nullptr);
    }
}

void APirateActorBase::RegisterDeadActor()
{
    if (GetWorldTimerManager().TimerExists(TimerHandle_LifeSpanExpired)) return;
    SetLifeSpan(1.0f);
    OnPirateDead.Broadcast(this);
}

void APirateActorBase::NextMoveToPoint()
{
    if (!CHECKED(StateBrain != EStateBrain::Idle, "State brain equal idle")) return;

    if (StateBrain == EStateBrain::WalkToStorage)
    {
        TargetIndex++;
        FVector NewPos = TargetSpline->GetSpline()->GetLocationAtSplinePoint(TargetIndex, ESplineCoordinateSpace::World);
        NewPos.Z += CapsuleCollision->GetScaledCapsuleHalfHeight();
        MovePirateComponent->GoAIMove(NewPos);
    }

    if (StateBrain == EStateBrain::WalkToBack)
    {
        TargetIndex--;
    }
}

#pragma endregion