// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/AI/Pirates/PirateActorBase.h"
#include "EffectManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATECLICKER_API UEffectManager : public UActorComponent
{
	GENERATED_BODY()

#pragma region Default

public:	
	UEffectManager();

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Data

    UPROPERTY()
    APirateActorBase* PirateActor;

#pragma endregion

#pragma region Effects

public:
    UFUNCTION()
    void ApplyFireEffect(float FireDamage,float FireDamagedDuration);

    UFUNCTION()
    void ApplyIceEffect(float IceSlow,float IceSlowDuration,float PirateMoveSpeed);

#pragma endregion
};
