// This section is the property of the Dverg Verksted team


#include "HealthComponent.h"

#include <wrl/wrappers/corewrappers.h>

#include "GameFramework/Actor.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	if (!GetOwner())
	{
		return;
	}
    Damage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(float TakenDamage)
{
    
    CurrentHealth = CurrentHealth - TakenDamage;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
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

