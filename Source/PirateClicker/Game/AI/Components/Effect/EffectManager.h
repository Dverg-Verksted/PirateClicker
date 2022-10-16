// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "EffectDataTypes.h"
#include "Components/ActorComponent.h"
#include "Game/AI/Pirates/PirateActorBase.h"
#include "EffectManager.generated.h"

UCLASS(ClassGroup = (Managers), HideCategories = ("Variable", "Sockets", "Tags", "ComponentTick", "ComponentReplication", "Activation", "Cooking", "Collision", "AssetUserData"),
    meta = (BlueprintSpawnableComponent))
class PIRATECLICKER_API UEffectManager : public UActorComponent
{
    GENERATED_BODY()

#pragma region Default

public:
    UEffectManager();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Data

protected:
    UPROPERTY(EditAnywhere, Category = "Settings effect manager", meta = (DisplayName = "Частота нанесения эффектов"))
    float CallApplyEffect{1.0f};

    UPROPERTY()
    UMoveComponent* OwnerMoveComponent;

    UPROPERTY()
    UAbilitySystemComponent* OwnerAbilitySystemComponent;

    TArray<FDataEffect> ArrayDataEffects;
    FTimerHandle ApplyEffectTimerHandle;
    FTimerHandle ResetEffectTimerHandle;

#pragma endregion

#pragma region Action

public:
    UFUNCTION(BlueprintCallable, Category = "Action")
    void AddEffect(const FDataEffect& InDataEffect);

    UFUNCTION(BlueprintCallable, Category = "Action")
    void RunApplyEffect();

    UFUNCTION(BlueprintCallable, Category = "Actor")
    void ResetEffects(const float InTime);

private:
    void ResetEffectManager();
    void ApplyEffectsToOwner();

#pragma endregion
};
