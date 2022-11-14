// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUserWidgetBase.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ETotems : uint8
{
    NONE UMETA(Hidden),
    Fire,
    Frost,
    ThirdType,
    FourthType,
};
ENUM_CLASS_FLAGS(ETotems);

UCLASS()
class PIRATECLICKER_API UGameUserWidgetBase : public UUserWidget
{
    GENERATED_BODY()
};
