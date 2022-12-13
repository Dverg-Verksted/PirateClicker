// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/LoreDiaryMasterWidget.h"

void ULoreDiaryMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LoreDiaryEditableText->SetVisibility(ESlateVisibility::Collapsed);

    BackDiaryButton->OnClicked.AddDynamic(this,&ThisClass::CloseDiaryEvent);
    Page1DiaryButton->OnClicked.AddDynamic(this,&ThisClass::OpenDiaryPageEvent);
    Page2DiaryButton->OnClicked.AddDynamic(this,&ThisClass::OpenDiaryPageEvent);
    Page3DiaryButton->OnClicked.AddDynamic(this,&ThisClass::OpenDiaryPageEvent);
}

void ULoreDiaryMasterWidget::OpenDiaryPageEvent()
{
    OpenDiaryPageNotify.Broadcast();
    PlayAnimation(OpenDiaryPageAnim);
    if (!LoreDiaryEditableText->IsVisible())
    {
        LoreDiaryEditableText->SetVisibility(ESlateVisibility::Visible);
    }
    
}
void ULoreDiaryMasterWidget::CloseDiaryEvent()
{
    CloseDiaryNotify.Broadcast();
    PlayAnimation(CloseDiaryAnim);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
}

