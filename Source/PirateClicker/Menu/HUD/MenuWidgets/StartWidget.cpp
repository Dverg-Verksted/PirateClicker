// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/StartWidget.h"

void UStartWidget::NativeConstruct()
{
    Super::NativeConstruct();

    StartGameButton->OnClicked.AddDynamic(this,&ThisClass::UStartWidget::OpenLevelSelectWidget);
    SettingsButton->OnClicked.AddDynamic(this,&ThisClass::UStartWidget::OpenSettingsWidget);
    LoreDiaryButton->OnClicked.AddDynamic(this,&ThisClass::OpenDiaryMenu);
}

void UStartWidget::OpenSettingsWidget()
{
    PlayAnimation(ButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::SettingsMenu);
}

void UStartWidget::OpenLevelSelectWidget()
{
    PlayAnimation(ButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::LevelSelectMenu);
}
void UStartWidget::OpenDiaryMenu()
{
    PlayAnimation(ButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::LoreDairyMenu);
}
