// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Menu/HUD/MenuMasterWidget.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATECLICKER_API USettingsWidget : public UMenuMasterWidget
{
	GENERATED_BODY()

#pragma region  WidgetComponents

public:
    
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* BackButton;
    UPROPERTY(Transient,meta = (BindWidget))
    UComboBoxString* GraphicsSettingsComboBox;

    UPROPERTY(Transient,meta = (BindWidget))
    UCheckBox* SoundsVolume;
    UPROPERTY(Transient,meta = (BindWidget))
    UCheckBox* MusicVolume;
    
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* BackButtonAnimation;
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* ButtonAnimation;

#pragma endregion

#pragma region Action

public:

    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void BackToStartMenuWidget();

    UFUNCTION()
    void ChangeMusicVolume(bool bIsMusicChecked);
    UFUNCTION()
    void ChangeSoundsVolume(bool bIsSoundsChecked);

#pragma endregion
	
};
