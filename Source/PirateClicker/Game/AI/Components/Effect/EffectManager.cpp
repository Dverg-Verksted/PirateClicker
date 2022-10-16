// This section is the property of the Dverg Verksted team

#include "Game/AI/Components/Effect/EffectManager.h"
#include "Game/AI/Components/AbilitySystemComponent.h"
#include "Game/AI/Components/MoveComponent.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

UEffectManager::UEffectManager()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UEffectManager::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(GetOwner() != nullptr, "Owner actor is nullptr")) return;

    OwnerAbilitySystemComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
    if (!CHECKED(OwnerAbilitySystemComponent != nullptr, "Ability component is nullptr")) return;

    OwnerMoveComponent = GetOwner()->FindComponentByClass<UMoveComponent>();
    if (!CHECKED(OwnerMoveComponent != nullptr, "Move component is nullptr")) return;

    ResetEffectManager();
}

void UEffectManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma endregion

#pragma region Action

void UEffectManager::AddEffect(const FDataEffect& InDataEffect)
{
    ArrayDataEffects.Add(InDataEffect);
    LOG_PIRATE(ELogVerb::Display, FString::Printf(TEXT("Add effect in Pirate: [%s] | Data: [%s]"), *GetOwner()->GetName(), *InDataEffect.ToString()));
    RunApplyEffect();
}

void UEffectManager::RunApplyEffect()
{
    if (!GetWorld()) return;

    if (!GetWorld()->GetTimerManager().TimerExists(ApplyEffectTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(ApplyEffectTimerHandle, this, &ThisClass::ApplyEffectsToOwner, CallApplyEffect, true);
    }
}

void UEffectManager::ResetEffects(const float InTime)
{
    if (!GetWorld()) return;

    if (!GetWorld()->GetTimerManager().TimerExists(ResetEffectTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(ResetEffectTimerHandle, this, &ThisClass::ResetEffectManager, InTime, false);
    }
}

void UEffectManager::ResetEffectManager()
{
    if (!GetWorld()) return;

    GetWorld()->GetTimerManager().ClearTimer(ResetEffectTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ApplyEffectTimerHandle);
    OwnerMoveComponent->ResetSpeedModifyToPercent();
    ArrayDataEffects.Empty();
}

void UEffectManager::ApplyEffectsToOwner()
{
    for (const FDataEffect& Data : ArrayDataEffects)
    {
        if (OwnerAbilitySystemComponent->IsDead())
        {
            ResetEffectManager();
            return;
        }

        switch (Data.TypeEffect)
        {
            case ETypeEffect::Fire:
            {
                OwnerAbilitySystemComponent->TakeDamage(GetOwner(), Data.Damage, nullptr, nullptr, nullptr);
                break;
            }
            case ETypeEffect::Cold:
            {
                OwnerMoveComponent->SetupSpeedModifyToPercent(Data.SpeedConversion);
                break;
            }
        }
    }
}

#pragma endregion
