// This section is the property of the Dverg Verksted team

#include "Game/AI/Pirates/AbilitySystemComponent.h"
#include "Library/PirateClickerLibrary.h"

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UAbilitySystemComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
    OnUpdateHealth.Broadcast(CurrentHealth);
    if (CurrentHealth <= 0.0f)
    {
        OnDeath.Broadcast();
    }
}

// Called when the game starts
void UAbilitySystemComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    if (!CHECKED(GetOwner() != nullptr, "Owner is nullptr")) return;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ThisClass::TakeDamage);
}
