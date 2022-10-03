// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Game/AI/Pirates/PirateActorBase.h"
#include "EffectObject.generated.h"


/**
 * 
 */

UENUM()
enum class EEffects : uint8
{
    IceEffect UMETA(DisplayName = "Эффект льда"),
    FireEffect UMETA(DisplayName = "Эффект огня")
};


UCLASS()
class PIRATECLICKER_API UEffectObject : public UObject
{
	GENERATED_BODY()
	
};

#pragma region Default

//PirateActor
APirateActorBase* PirateActor;

//Effects
float FireDamage{0};
float FireDamageCauseTime{0};

float IceSlowMovement {0};

#pragma endregion 
