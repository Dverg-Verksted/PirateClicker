// This section is the property of the Dverg Verksted team

#include "Game/AI/Components/AbilitySystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
static TAutoConsoleVariable<bool> EnableD_HealthPirate(TEXT("Pirate.ShowHealth"), false, TEXT("Enable debug information about the health of pirates"), ECVF_Cheat);
static TAutoConsoleVariable<bool> EnableD_StaminaPirate(TEXT("Pirate.ShowStamina"), false, TEXT("Enable debug information about the stamina of pirates"), ECVF_Cheat);
#endif

#pragma region Default

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

// Called when the game starts
void UAbilitySystemComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(GetOwner() != nullptr, "Owner is nullptr")) return;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ThisClass::RegisterTakeDamage);

    GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);

    StartAbilitySystem();
}

void UAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG

    if (EnableD_HealthPirate.GetValueOnGameThread())
    {
        DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), DataHealth.ToStringN(), nullptr, FColor::Orange, 0.0f, false, 1.0f);
    }

    if (EnableD_StaminaPirate.GetValueOnGameThread())
    {
        DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), DataStamina.ToStringN(), nullptr, FColor::Orange, 0.0f, false, 1.0f);
    }

#endif
}

#pragma endregion

#pragma region Action

void UAbilitySystemComponent::InitAbilityData(const bool bInEnableHealth, const FDataHealth& InDataHealth, const bool bInEnableStamina, const FDataStamina& InDataStamina)
{
    if (!CHECKED(StatusAbilitySystem != EStatusAbilitySystem::Init, "Status ability system is Init!")) return;

    bEnableHealth = bInEnableHealth;
    DataHealth = InDataHealth;
    bEnableStamina = bInEnableStamina;
    DataStamina = InDataStamina;
    bDead = false;

    ChangeStatusAbilitySystem(EStatusAbilitySystem::Init);
}

void UAbilitySystemComponent::ResetAbilityData()
{
    if (!CHECKED(StatusAbilitySystem != EStatusAbilitySystem::Reset, "Status ability system is Reset!")) return;

    GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(FillHealthTimerHandle);

    bEnableHealth = false;
    DataHealth.Empty();
    bEnableStamina = false;
    DataStamina.Empty();
    bDead = false;

    ChangeStatusAbilitySystem(EStatusAbilitySystem::Reset);
}

void UAbilitySystemComponent::StartAbilitySystem()
{
    if (!CHECKED(StatusAbilitySystem == EStatusAbilitySystem::Init, "Status ability system is not init!")) return;

    if (bEnableHealth)
    {
        DataHealth.Init();
        OnUpdateDataHealth.Broadcast(DataHealth);
        if (DataHealth.bRegenerateHealth)
        {
            GetWorld()->GetTimerManager().SetTimer(FillHealthTimerHandle, this, &ThisClass::FillHealth, DataHealth.CallFrequencyUpperHealth, true);
        }
    }

    if (bEnableStamina)
    {
        DataStamina.Init();
        OnUpdateDataStamina.Broadcast(DataStamina);
    }

    ChangeStatusAbilitySystem(EStatusAbilitySystem::Run);
}

void UAbilitySystemComponent::StartReduceStamina()
{
    if (!CHECKED(StatusAbilitySystem == EStatusAbilitySystem::Run, "Status ability system is not Run!")) return;

    GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);

    if (!GetWorld()->GetTimerManager().TimerExists(ReduceStaminaTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(ReduceStaminaTimerHandle, this, &ThisClass::ReduceStamina, DataStamina.CallFrequencyReduceStamina, true);
    }
}

void UAbilitySystemComponent::StopReduceStamina()
{
    if (!CHECKED(StatusAbilitySystem == EStatusAbilitySystem::Run, "Status ability system is not Run!")) return;

    GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);

    if (DataStamina.bRegenerateStamina)
    {
        GetWorld()->GetTimerManager().SetTimer(FillStaminaTimerHandle, this, &ThisClass::FillStamina, DataStamina.CallFrequencyUpperStamina, true);
    }
}

void UAbilitySystemComponent::TakeDamage(const float Damage)
{
    RegisterTakeDamage(nullptr, Damage, nullptr, nullptr, nullptr);
}

void UAbilitySystemComponent::RegisterTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (!CHECKED(StatusAbilitySystem == EStatusAbilitySystem::Run, "Status ability system is not Run!")) return;

    if (bEnableHealth && !bDead)
    {
        DataHealth.Health = FMath::Clamp(DataHealth.Health - Damage, 0.0f, DataHealth.MaxHealth);
        OnUpdateDataHealth.Broadcast(DataHealth);
        if (FMath::IsNearlyZero(DataHealth.Health))
        {
            bDead = true;
            OnDeath.Broadcast();
            GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);
            GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);
            GetWorld()->GetTimerManager().ClearTimer(FillHealthTimerHandle);

            ChangeStatusAbilitySystem(EStatusAbilitySystem::None);
        }
    }
}

void UAbilitySystemComponent::FillHealth()
{
    DataHealth.CallStepFillHealth();
}

void UAbilitySystemComponent::ReduceStamina()
{
    DataStamina.CallStepReduceStamina();
    if (FMath::IsNearlyZero(DataStamina.Stamina))
    {
        GetWorld()->GetTimerManager().ClearTimer(ReduceStaminaTimerHandle);
        OnStaminaIsOver.Broadcast();
        StopReduceStamina();
    }
}

void UAbilitySystemComponent::FillStamina()
{
    DataStamina.CallStepFillStamina();
    if (DataStamina.IsStaminaFull())
    {
        GetWorld()->GetTimerManager().ClearTimer(FillStaminaTimerHandle);
        OnStaminaIsFull.Broadcast();
        StartReduceStamina();
    }
}

#pragma endregion

void UAbilitySystemComponent::ChangeStatusAbilitySystem(const EStatusAbilitySystem& NewStatus)
{
    if (!CHECKED(StatusAbilitySystem != NewStatus, "Status ability system is equal new status")) return;
    StatusAbilitySystem = NewStatus;
    OnUpdateStatusAbilitySystem.Broadcast(NewStatus);
}
