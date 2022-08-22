// This section is the property of the Dverg Verksted team


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdateSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);

UCLASS(ClassGroup=(Custom),HideCategories =("Variable","Sockets","Tags","ComponentTick","ComponentReplication","Activation","Cooking","Collision","AssetUserData"), meta=(BlueprintSpawnableComponent))
class PIRATECLICKER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable,Category = "Damage and Health",meta =(ToolTip="Дай мне свой урон"))
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
    
	void TakeHeal(float TakenDamage,float TakeHeal); // <-- this function isn't working for now. Maybe we can use it later

    UFUNCTION (BlueprintCallable,Category = "Damage and Health",meta = (ToolTip = "Функция для получения текущего хп актера"))
    float GetCurrentHealth();
    UFUNCTION(BlueprintCallable,Category = "Damage and Health", meta = (ToolTip =" Функция для получения максимального хп актера"))
    float GetMaxHealth();
    
    UFUNCTION (BlueprintCallable,Category = "Damage and Health",meta =(ToolTip = "Функция для изменения максимального хп актера"))
    void SetMaxHealth(float HealthToSet);
    
	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category = "Damage and Health Dispatchers")
	FHealthUpdateSignature OnUpdateHealth;
    UPROPERTY(BlueprintAssignable,BlueprintCallable,Category = "Damage and Health Dispatchers")
    FDeathSignature OnDeath;
    
private:
    
	UPROPERTY(EditAnywhere,Category = "Health Settings",meta =(ClampMin ="0",ForceUnits = "%",ToolTip = "Здесь можно изменять максимальное хп актера с этим компонентом"))
	float MaxHealth = 100;
    
	float CurrentHealth = 0;

protected:
	virtual void BeginPlay() override;
};