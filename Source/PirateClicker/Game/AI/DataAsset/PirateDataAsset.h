// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PirateDataAsset.generated.h"

class APirateActorBase;

USTRUCT(BlueprintType)
struct FDataPirate
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TSubclassOf<APirateActorBase> SubClassPirate;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "1", DisplayName = "Жизни пирата"))
    int32 Health{100};

    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Скорость передвижения пирата", ClampMin = "0.1", ClampMax = "1500.0", ForceUnits = "m/s"))
    float SpeedMove{10.0f};

    // Rotate speed pirate
    UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Скорость поворота пирата", ClampMin = "0.1", ClampMax = "5.0", ForceUnits = "x"))
    float SpeedRotate{1.0f};

    FString ToString() const { return FString::Printf(TEXT("Health: [%i] | Speed Move: [%f] m/s | Speed Rotate: [%f]"), this->Health, this->SpeedMove, this->SpeedRotate); }
};

/**
 * @class Pirate data asset
 */
UCLASS()
class PIRATECLICKER_API UPirateDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /**
     * @public Get data pirate
     * @return FDataPirate
     **/
    UFUNCTION(BlueprintCallable, Category = "UPirateDataAsset | GetData")
    FORCEINLINE FDataPirate GetDataPirate() const { return DataPirate; }

private:
    UPROPERTY(EditAnywhere, Category = "Settings Pirate", meta = (ShowOnlyInnerProperties))
    FDataPirate DataPirate;
};
