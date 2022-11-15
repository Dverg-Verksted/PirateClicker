// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/LevelSelectWidget.h"

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LevelSwitchLeftArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLvlAtScreenLeft);
    LevelSwitchRightArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLevelAtScreenRight);
    BackButton->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::BackToStartMenuWidget);
}

void ULevelSelectWidget::MoveLevelAtScreenRight()
{
    if (isLastLvlSelected)return;

    PlayAnimation(ArrowButtonsAnimation);
    LevelNumber++;
}
void ULevelSelectWidget::MoveLvlAtScreenLeft()
{
    if (isFirstLvlSelected)return;

    PlayAnimation(ArrowButtonsAnimation);
    LevelNumber--;
}

void ULevelSelectWidget::BackToStartMenuWidget()
{
    PlayAnimation(BackButtonsAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
}

