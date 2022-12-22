// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/WidgetsComponents/LoreDiaryPageButtonComponent.h"

void ULoreDiaryPageButtonComponent::NativeConstruct()
{
    Super::NativeConstruct();
    
    DiaryPageTextBlock->SetText(DiaryPageButtonName);
    
}
void ULoreDiaryPageButtonComponent::OpenDiaryPageEvent()
{
    OnOpenDiaryPageNotify.Broadcast(DiaryPageButtonName,DiaryPageButtonLoreText);
}

FText ULoreDiaryPageButtonComponent::GetDiaryPageNameEvent()
{
    return DiaryPageButtonName;
}
FText ULoreDiaryPageButtonComponent::GetDiaryPageTextBlockEvent()
{
    return DiaryPageButtonLoreText;
}

