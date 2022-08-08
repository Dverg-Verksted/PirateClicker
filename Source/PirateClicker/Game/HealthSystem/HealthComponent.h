// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageSignature,float,TakenDamage, float,TakenHeal);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATECLICKER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable,Category = "Damage")
	float TakeDamage(float TakenDamage,float TakeHeal);

	UFUNCTION(BlueprintCallable,Category = "Heal")
	float TakeHeal(float TakenDamage,float TakeHeal);

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category = "Damage")
	FDamageSignature Damage;

	
private:
	UPROPERTY(EditAnywhere,Category = "Health settings")
	float MaxHealth = 100;
	
	float CurrentHealth = MaxHealth;

protected:
	virtual void BeginPlay() override;
};