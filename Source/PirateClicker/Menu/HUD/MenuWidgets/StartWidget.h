// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Menu/HUD/MenuMasterWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATECLICKER_API UStartWidget : public UMenuMasterWidget
{
	GENERATED_BODY()

#pragma region  WidgetComponents

public:
    
    UPROPERTY(Transient,meta = (BindWidget))
    UCanvasPanel* WidgetCanvasPanel;
    
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* StartGameButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* SettingsButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* OptionsButton;

    UPROPERTY(Transient, meta = (BindWidget))
    UWidgetAnimation* ButtonAnimation;

#pragma endregion

#pragma region Actions

private:
    
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OpenLevelSelectWidget();
    UFUNCTION()
    void OpenSettingsWidget();

#pragma endregion 
};
