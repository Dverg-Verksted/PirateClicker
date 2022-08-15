// This section is the property of the Dverg Verksted team


#include "HealthComponent.h"
#include "Library/PirateClickerLibrary.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    CurrentHealth = MaxHealth;
    
	if (!CHECKED(GetOwner() !=nullptr, "Owner is nullptr")) return;
    Damage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(float TakenDamage)
{
    CurrentHealth = FMath::Clamp(CurrentHealth - TakenDamage,0.0f,MaxHealth);
	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::TakeHeal(float TakenHeal,float TakenDamage)  // <-- this function isn't working for now. Maybe we can use it later
{
    CurrentHealth = CurrentHealth + TakenHeal;
	    if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float UHealthComponent::GetCurrentHealth()
{
    return CurrentHealth;
}
float UHealthComponent::GetMaxHealth()
{
    return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float HealthToSet)
{
    MaxHealth = HealthToSet;
}


