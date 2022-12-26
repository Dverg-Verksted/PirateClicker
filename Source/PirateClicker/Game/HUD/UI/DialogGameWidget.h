// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Game/HUD/UI/GameUserWidgetBase.h"
#include "Game/GameMode/StoryGMDataTypes.h"
#include "DialogGameWidget.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class PIRATECLICKER_API UDialogGameWidget : public UGameUserWidgetBase
{
    GENERATED_BODY()

#pragma region Default

protected:
    virtual void InitWidget() override;

#pragma endregion

#pragma region ActionDialog

public:
    UFUNCTION(BlueprintImplementableEvent)
    void PushDataDialog_Event(const FDialogData& DataDialog, const bool bEnd);

private:
    UFUNCTION()
    void PushDataDialog();

    void CompleteDialog();

#pragma endregion

#pragma region DataDialog

protected:
    UPROPERTY(Transient, meta = (BindWidget))
    UButton* NextPushDataDialog;

private:
    EStateGame NextStateGame{EStateGame::None};

    TArray<FDialogData> ArrayDataDialogs;

    int32 TargetIndexDialog{0};

#pragma endregion
};
