// This section is the property of the Dverg Verksted team


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageSignature,float,TakenDamage);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PIRATECLICKER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable,Category = "Damage and Health")
	void TakeDamage(float TakenDamage);
    
	void TakeHeal(float TakenDamage,float TakeHeal); // <-- this function isn't working for now. Maybe we can use it later

    UFUNCTION (BlueprintCallable,Category = "Damage and Health")
    float GetCurrentHealth();
    
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category = "Damage and Health")
	FDamageSignature Damage;
    
private:
    
	UPROPERTY(EditAnywhere,Category = "Health Settings")
	float MaxHealth = 100;
    UPROPERTY(VisibleAnywhere,Category = "Health Settings")
	float CurrentHealth = MaxHealth;

protected:
	virtual void BeginPlay() override;
};