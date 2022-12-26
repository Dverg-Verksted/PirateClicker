// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
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
    UButton* StartGameButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* SettingsButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* ShopButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* LoreDiaryButton;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* ButtonAnimation;

#pragma endregion

#pragma region Actions

private:
    
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OpenLevelSelectWidget();
    UFUNCTION()
    void OpenSettingsWidget();
    UFUNCTION()
    void OpenDiaryMenu();

#pragma endregion 
};
