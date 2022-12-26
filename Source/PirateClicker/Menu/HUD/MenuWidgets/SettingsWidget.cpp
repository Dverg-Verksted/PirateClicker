// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/SettingsWidget.h"

void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BackButton->OnClicked.AddDynamic(this,&ThisClass::USettingsWidget::BackToStartMenuWidget);
    MusicVolume->OnCheckStateChanged.AddDynamic(this,&ThisClass::ChangeMusicVolume);
    SoundsVolume->OnCheckStateChanged.AddDynamic(this,&ThisClass::ChangeSoundsVolume);
}

void USettingsWidget::BackToStartMenuWidget()
{
    PlayAnimation(BackButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
}

void USettingsWidget::ChangeMusicVolume(bool bIsMusicChecked)
{
    
}

void USettingsWidget::ChangeSoundsVolume(bool bIsSoundsChecked)
{
    
}

