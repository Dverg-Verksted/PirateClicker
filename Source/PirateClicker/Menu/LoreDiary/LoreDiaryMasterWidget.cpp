// This section is the property of the Dverg Verksted team


#include "Menu/LoreDiary/LoreDiaryMasterWidget.h"

void ULoreDiaryMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    ChangePageLeftNotify.AddDynamic(this,&ThisClass::ChangePageLeftEvent);
    ChangePageRightNotify.AddDynamic(this,&ThisClass::ChangePageRightEvent);
}

void ULoreDiaryMasterWidget::ChangePageLeftEvent()
{
    if (CanChangePage==false) return;
    if (CanChangePage==true)
    {
        CanChangePage=false;
        PlayAnimation(ChangePageLeftAnimation);
        CanChangePage=true;
    }
}

void ULoreDiaryMasterWidget::ChangePageRightEvent()
{
    if (CanChangePage==false) return;
    if (CanChangePage==true)
    {
        CanChangePage = false;
        PlayAnimation(ChangePageRightAnimation);
        CanChangePage = true;
        ;
    }
}

