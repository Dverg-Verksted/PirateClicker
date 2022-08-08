// This section is the property of the Dverg Verksted team


#include "HealthComponent.h"


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
	//Damage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

float UHealthComponent::TakeDamage(float TakenDamage,float TakenHeal)
{
	CurrentHealth = CurrentHealth - TakenDamage;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
	}
	return CurrentHealth;
}

float UHealthComponent::TakeHeal(float TakenHeal,float TakenDamage)
{
	CurrentHealth = CurrentHealth + TakenHeal;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
	return CurrentHealth;
}

