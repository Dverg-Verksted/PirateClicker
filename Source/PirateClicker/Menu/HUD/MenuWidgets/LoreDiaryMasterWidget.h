// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
//can delete later
#include "Components/MultiLineEditableTextBox.h"
//
#include "Delegates/DelegateCombinations.h"
#include "Menu/HUD/MenuMasterWidget.h"
#include "LoreDiaryMasterWidget.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDiaryPageSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseDiarySignature);

#pragma endregion

UCLASS()
class PIRATECLICKER_API ULoreDiaryMasterWidget : public UMenuMasterWidget
{
    GENERATED_BODY()

#pragma region Action

protected:
    virtual void NativeConstruct() override;

public:

    UFUNCTION()
    void OpenDiaryPageEvent();
    UFUNCTION()
    void CloseDiaryEvent();
    UFUNCTION()
    void ShowDiaryPageTextEvent();

#pragma endregion

#pragma region Components

    UPROPERTY(Transient,meta = (BindWidget))
    UButton* BackDiaryButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* Page1DiaryButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* Page2DiaryButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* Page3DiaryButton;
    
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* OpenDiaryPageAnim;
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* CloseDiaryAnim;

#pragma endregion

#pragma region Variables

protected:
    
    FOpenDiaryPageSignature OpenDiaryPageNotify;
    FCloseDiarySignature CloseDiaryNotify;

    //can delete later or recreate
    UPROPERTY(Transient,meta = (BindWidget))
    UMultiLineEditableTextBox* LoreDiaryText;
    //
#pragma endregion
    
	
};
