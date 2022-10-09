// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

//Fire Effect params
float FireDamage{0};
float FireDamageDuration{0};

//Ice Effect params
float IceSlowMovement {0};
float IceSlowMovementDuration {0};

#pragma endregion 
