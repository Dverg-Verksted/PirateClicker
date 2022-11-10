// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/StartWidget.h"

void UStartWidget::NativeConstruct()
{
    Super::NativeConstruct();

    StartGameButton->OnClicked.AddDynamic(this,&ThisClass::UStartWidget::OpenLevelSelectWidget);
    SettingsButton->OnClicked.AddDynamic(this,&ThisClass::UStartWidget::OpenSettingsWidget);
}

void UStartWidget::OpenSettingsWidget()
{
    
}

void UStartWidget::OpenLevelSelectWidget()
{
    
}
