// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PirateDataAsset.generated.h"

class APirateActorBase;
/**
 * @class Pirate data asset
 */
UCLASS()
class PIRATECLICKER_API UPirateDataAsset : public UDataAsset
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Settings Pirate")
    TSubclassOf<APirateActorBase> ClassPirate;

    UPROPERTY(EditAnywhere, Category = "Settings Pirate", meta = (ClampMin = "1", DisplayName = "Жизни пирата"))
    int32 Health{100};

    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, Category = "Settings Pirate",
        meta = (ToolTip = "Скорость передвижения пирата", ClampMin = "0.1", ClampMax = "1500.0", ForceUnits = "m/s"))
    float SpeedMove{10.0f};

    // Rotate speed pirate 
    UPROPERTY(EditDefaultsOnly, Category = "Settings Pirate",
        meta = (ToolTip = "Скорость поворота пирата", ClampMin = "0.1", ClampMax = "5.0", ForceUnits = "x"))
    float SpeedRotate{1.0f};
};
