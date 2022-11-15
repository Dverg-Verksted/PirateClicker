// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/SettingsWidget.h"

void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BackButton->OnClicked.AddDynamic(this,&ThisClass::USettingsWidget::BackToStartMenuWidget);
    
}

void USettingsWidget::BackToStartMenuWidget()
{
    PlayAnimation(BackButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
}
