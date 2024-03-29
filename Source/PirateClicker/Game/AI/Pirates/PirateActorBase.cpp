// This section is the property of the Dverg Verksted team

#include "Game/AI/Pirates/PirateActorBase.h"
#include "Game/AI/Components/AbilitySystemComponent.h"
#include "Game/AI/Components/MoveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Game/AI/Spawner/SplineActor.h"
#include "Game/Player/GamePC.h"
#include "Kismet/GameplayStatics.h"
#include "Library/PirateClickerLibrary.h"
#include "Game/GoldChest/GoldChest.h"
#include "Game/GoldStorage/GoldStorageActor.h"
#include "Engine/EngineTypes.h"
#include "Game/AI/Components/Effect/EffectManager.h"

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

    MoveComponent = CreateDefaultSubobject<UMoveComponent>(FName("Movement pirate component"));
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(FName("Ability system component"));
    EffectManager = CreateDefaultSubobject<UEffectManager>(FName("Effect manager"));
}

void APirateActorBase::InitParamsPirate(const FDataPirate& DataPirate, ASplineActor* NewSpline)
{
    if (!CHECKED(StateBrain == EStateBrain::NoneInit, "Pirate is init!")) return;

    MoveComponent->InitMoveData(DataPirate.SpeedMove, DataPirate.SpeedRotate);
    AbilitySystem->ResetAbilityData();
    AbilitySystem->InitAbilityData(DataPirate.bEnableHealth, DataPirate.DataHealth, DataPirate.bEnableStamina, DataPirate.DataStamina);
    SetupTargetSpline(NewSpline);
}

// Called when the game starts or when spawned
void APirateActorBase::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(CapsuleCollision != nullptr, "Capsule collision is nullptr")) return;
    if (!CHECKED(PirateMesh != nullptr, "Skeletal mesh is nullptr")) return;
    if (!CHECKED(MoveComponent != nullptr, "Movement pirate component is nullptr")) return;
    if (!CHECKED(TargetSpline != nullptr, "Target spline is nullptr")) return;
    if (!CHECKED(TargetSpline->GetSpline() != nullptr, "Spline is nullptr")) return;
    if (!CHECKED(AbilitySystem != nullptr, "AbilitySystem is nullptr")) return;
    AbilitySystem->OnDeath.AddDynamic(this, &ThisClass::RegisterDeadActor);
    AbilitySystem->StartAbilitySystem();
    if (AbilitySystem->IsEnableStamina())
    {
        AbilitySystem->StartReduceStamina();
        AbilitySystem->OnStaminaIsOver.AddDynamic(this, &ThisClass::RegisterStaminaOver);
        AbilitySystem->OnStaminaIsFull.AddDynamic(this, &ThisClass::RegisterStaminaFull);
    }

    const AGamePC* GamePC = Cast<AGamePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!CHECKED(GamePC != nullptr, "Game player controller is nullptr")) return;

    SetupStateBrain(EStateBrain::WalkToStorage);
}

#pragma endregion

#pragma region Action

void APirateActorBase::SetupTargetSpline(ASplineActor* NewSpline)
{
    if (!CHECKED(NewSpline != nullptr, "New Spline is nullptr")) return;

    TargetSpline = NewSpline;
    MoveToPoint();
}

void APirateActorBase::SetupStateBrain(const EStateBrain NewState)
{
    if (!CHECKED(StateBrain != NewState, "Current state brain == New State")) return;

    LOG_PIRATE(ELogVerb::Display, FString::Printf(TEXT("New brain state: [%s]"), *UEnum::GetValueAsString(NewState)));
    LastStateBrain = StateBrain;
    StateBrain = NewState;
    OnChangeStateBrain.Broadcast(StateBrain);

    if (StateBrain == EStateBrain::WalkToBack || StateBrain == EStateBrain::WalkToStorage)
    {
        MoveToPoint();
    }
}

void APirateActorBase::RegisterDeadActor()
{
    if (GetWorldTimerManager().TimerExists(TimerHandle_LifeSpanExpired)) return;
    BackChestToStorage();
    SetLifeSpan(1.0f);
    OnPirateDead.Broadcast(this);
    MoveComponent->StopMovement();
    PlayMontage(DeadMontage);
}

void APirateActorBase::MoveToPoint() const
{
    if (!TargetSpline) return;
    if (StateBrain != EStateBrain::WalkToBack && StateBrain != EStateBrain::WalkToStorage) return;
    
    const int32 Index = UPirateClickerLibrary::GetIndexAlongDistTargetPosition(TargetSpline, GetActorLocation());
    const float Duration = FMath::Clamp(TargetSpline->GetSpline()->GetDistanceAlongSplineAtSplinePoint(Index) / TargetSpline->GetSpline()->GetSplineLength(), 0.0f, 1.0f);
    const bool bRev = StateBrain == EStateBrain::WalkToBack;
    MoveComponent->GoMove(FMovementData(Duration, bRev, TargetSpline));
}

void APirateActorBase::SpawnGoldChest(const TSubclassOf<AGoldChest>& SubClassGoldChest, AGoldStorageActor* GoldStorageActor)
{
    GoldStorageFrom = GoldStorageActor;
    GoldChest = GetWorld()->SpawnActor<AGoldChest>(SubClassGoldChest, FActorSpawnParameters());
    if (!CHECKED(GoldChest != nullptr, "Gold chest is nullptr")) return;
    GoldChest->AttachToComponent(PirateMesh, FAttachmentTransformRules::KeepRelativeTransform, (FName("middle_01_lSocket")));
    bHasTreasure = true;
    OnStatusTreasure.Broadcast(bHasTreasure);
}

float APirateActorBase::PlayMontage(UAnimMontage* AnimMontage, const float InPlayRate, const FName StartSectionName) const
{
    UAnimInstance * AnimInstance = (PirateMesh) ? PirateMesh->GetAnimInstance() : nullptr;
    if (AnimMontage && AnimInstance)
    {
        float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

        if (Duration > 0.f)
        {
            // Start at a given Section.
            if (StartSectionName != NAME_None)
            {
                AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
            }

            return Duration;
        }
    }

    return 0.f;
}

void APirateActorBase::BackChestToStorage()
{
    if (!bHasTreasure || !GoldStorageFrom) return;

    GoldStorageFrom->UpperCountGold();
    if (GoldChest)
    {
        GoldChest->Destroy();
    }
    bHasTreasure = false;
    OnStatusTreasure.Broadcast(bHasTreasure);
}

void APirateActorBase::RegisterStaminaOver()
{
    // Pause move
    SetupStateBrain(EStateBrain::WaitFor);
    MoveComponent->PauseMove();
}

void APirateActorBase::RegisterStaminaFull()
{
    // Resume move

    const EStateBrain Temp = LastStateBrain;
    LastStateBrain = StateBrain;
    StateBrain = Temp;
    OnChangeStateBrain.Broadcast(StateBrain);
    MoveComponent->ResumeMove();
}

#pragma endregion
