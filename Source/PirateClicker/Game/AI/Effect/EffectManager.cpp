// This section is the property of the Dverg Verksted team

#include "Game/AI/Effect/EffectManager.h"
#include "Game/AI/Pirates/AbilitySystemComponent.h"
#include "Game/AI/Pirates/MovePirateComponent.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

UEffectManager::UEffectManager()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UEffectManager::BeginPlay()
{
    Super::BeginPlay();

    OwnerPirateActor = Cast<APirateActorBase>(GetOwner());
    if (!CHECKED(OwnerPirateActor != nullptr, "Owner pirate actor is nullptr")) return;

    OwnerAbilitySystemComponent = OwnerPirateActor->FindComponentByClass<UAbilitySystemComponent>();
    if (!CHECKED(OwnerAbilitySystemComponent != nullptr, "Ability component is nullptr")) return;

    OwnerMovePirateComponent = OwnerPirateActor->FindComponentByClass<UMovePirateComponent>();
    if (!CHECKED(OwnerMovePirateComponent != nullptr, "Move component is nullptr")) return;

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
    LOG_PIRATE(ELogVerb::Display, FString::Printf(TEXT("Add effect in Pirate: [%s] | Data: [%s]"), *OwnerPirateActor->GetName(), *InDataEffect.ToString()));
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
                OwnerAbilitySystemComponent->TakeDamage(OwnerPirateActor, Data.Damage, nullptr, nullptr, nullptr);
            }
            case ETypeEffect::Cold:
            {
            }
        }
    }
}

#pragma endregion
