// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUserWidgetBase.generated.h"

/**
 *
 */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ETotems : uint8
{
    NONE = 0 UMETA(Hidden),
    Fire = 1 << 0,
    Frost = 1 << 1,
    ThirdType = 1 << 2,
    FourthType = 1 << 3,
};
ENUM_CLASS_FLAGS(ETotems);

UCLASS()
class PIRATECLICKER_API UGameUserWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ETotems"))
    //uint8 TotemFlags = 0;

    UFUNCTION(BlueprintCallable)
    static  void SetTotemsToHUD(UPARAM(meta = (Bitmask, BitmaskEnum = ETotems)) int32 Totems, bool& Fire, bool& Frost, bool& ThirdType, bool& FourthType);
};
