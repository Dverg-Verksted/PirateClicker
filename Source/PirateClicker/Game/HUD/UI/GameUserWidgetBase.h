// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUserWidgetBase.generated.h"

class AStoryGMBase;
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

#pragma region Default

public:
    virtual void InitWidget()
    {
        InitWidget_Event();
    }
    virtual void CompleteWidget()
    {
        CompleteWidget_Event();
    }

protected:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintImplementableEvent)
    void InitWidget_Event();

    UFUNCTION(BlueprintImplementableEvent)
    void CompleteWidget_Event();

#pragma endregion

#pragma region GameUserData

protected:
    UPROPERTY(BlueprintReadOnly)
    AStoryGMBase* StoryGM;

#pragma endregion
};
