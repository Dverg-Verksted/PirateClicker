// This section is the property of the Dverg Verksted team


#include "HealthComponent.h"

#include "GameFramework/Actor.h"
#include "Library/PirateClickerLibrary.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    CurrentHealth = MaxHealth;
    
	if (!CHECKED(GetOwner() !=nullptr, "Owner is nullptr")) return;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    CurrentHealth = FMath::Clamp(CurrentHealth - Damage,0.0f,MaxHealth);
    OnUpdateHealth.Broadcast(CurrentHealth);
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


