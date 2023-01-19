// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Delegates/DelegateCombinations.h"
#include "Menu/HUD/MenuMasterWidget.h"
#include "Menu/HUD/MenuWidgets/WidgetsComponents/LoreDiaryPageButtonComponent.h"
#include "LoreDiaryMasterWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseDiarySignature);

UCLASS()
class PIRATECLICKER_API ULoreDiaryMasterWidget : public UMenuMasterWidget
{
    GENERATED_BODY()

#pragma region Action

protected:
    virtual void NativeConstruct() override;

public:
    
    UFUNCTION()
    void CloseDiaryEvent();
    UFUNCTION(BlueprintCallable)
    void ShowDiaryPageTextEvent(FText LoreDiaryTextToShow,FText LoreDiaryTextName);
    UFUNCTION(BlueprintCallable)
    void CreateNewButtonComponentEvent(FText LoreDiaryTextToShow,FText LoreDiaryTextName);

private:
    UFUNCTION()
    void RegisterClickedButtonPage(class ULoreDiaryPageButtonComponent* PageButton);


#pragma endregion

#pragma region Components

    UPROPERTY(Transient,meta = (BindWidget))
    UButton* BackDiaryButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UTextBlock* LoreDiaryText;
    UPROPERTY(Transient,meta = (BindWidget))
    UVerticalBox* LoreDiaryButtonsContainer;
    
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* CloseDiaryAnim;

#pragma endregion

#pragma region Variables

protected:
    
    FCloseDiarySignature CloseDiaryNotify;
    UPROPERTY(EditAnywhere)
    TSubclassOf<ULoreDiaryPageButtonComponent> LoreDiaryButtonClass;

#pragma endregion
    
};
