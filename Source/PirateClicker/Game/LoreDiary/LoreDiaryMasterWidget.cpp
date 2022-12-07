// This section is the property of the Dverg Verksted team


#include "Game/LoreDiary/LoreDiaryMasterWidget.h"

void ULoreDiaryMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    ChangePageLeftNotify.AddDynamic(this,&ThisClass::ChangePageLeftEvent);
    ChangePageRightNotify.AddDynamic(this,&ThisClass::ChangePageRightEvent);
}

EDiaryState ULoreDiaryMasterWidget::GetCurrentDiaryState()
{
    return CurrentDiaryState;
}

void ULoreDiaryMasterWidget::SetMaxPageAmount(int32 NewMaxPageAmount)
{
    MaxPageAmount = NewMaxPageAmount;
}

void ULoreDiaryMasterWidget::ChangePageLeftEvent()
{
    if (CurrentDiaryState==EDiaryState::None) return;
    if (CurrentPageNumber == MinPageAmount) return;
    if (CurrentDiaryState==EDiaryState::Reading)
    {
        CurrentDiaryState = EDiaryState::ChangingPage;
        CurrentPageNumber--;
        PlayAnimation(ChangePageLeftAnimation);
        CurrentDiaryState = EDiaryState::Reading;
    }
}

void ULoreDiaryMasterWidget::ChangePageRightEvent()
{
    if (CurrentDiaryState==EDiaryState::None) return;
    if (CurrentPageNumber == MaxPageAmount) return;
    if (CurrentDiaryState==EDiaryState::Reading)
    {
        CurrentDiaryState = EDiaryState::ChangingPage;
        CurrentPageNumber++;
        PlayAnimation(ChangePageRightAnimation);
        CurrentDiaryState = EDiaryState::Reading;
    }
}

