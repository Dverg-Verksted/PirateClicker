// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/WidgetsComponents/LoreDiaryPageButtonComponent.h"

void ULoreDiaryPageButtonComponent::NativeConstruct()
{
    Super::NativeConstruct();
    
    DiaryPageTextBlock->SetText(DiaryPageButtonName);
    DiaryPageButton->OnClicked.AddDynamic(this,&ULoreDiaryPageButtonComponent::OpenDiaryPageEvent);
    
}
void ULoreDiaryPageButtonComponent::OpenDiaryPageEvent()
{
    OnOpenDiaryPageNotify.Broadcast(this);
}

