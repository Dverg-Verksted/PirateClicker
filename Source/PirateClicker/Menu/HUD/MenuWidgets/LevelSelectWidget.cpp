// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/LevelSelectWidget.h"

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LevelSwitchLeftArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLvlAtScreenLeft);
    LevelSwitchRightArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLevelAtScreenRight);
}

void ULevelSelectWidget::MoveLevelAtScreenRight()
{
    if (isLastLvlSelected)return;
    
}
void ULevelSelectWidget::MoveLvlAtScreenLeft()
{
    if (isFirstLvlSelected)return;
    
}

