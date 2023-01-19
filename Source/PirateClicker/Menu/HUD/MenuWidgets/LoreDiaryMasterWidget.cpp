// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/LoreDiaryMasterWidget.h"
#include "WidgetsComponents/LoreDiaryPageButtonComponent.h"

void ULoreDiaryMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LoreDiaryText->SetVisibility(ESlateVisibility::Collapsed);
    BackDiaryButton->OnClicked.AddDynamic(this,&ThisClass::CloseDiaryEvent);
}
void ULoreDiaryMasterWidget::CloseDiaryEvent()
{
    CloseDiaryNotify.Broadcast();
    PlayAnimation(CloseDiaryAnim);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
    LoreDiaryText->SetVisibility(ESlateVisibility::Collapsed);
}
void ULoreDiaryMasterWidget::ShowDiaryPageTextEvent(FText LoreDiaryTextToShow,FText LoreDiaryTextName)
{
    if (LoreDiaryText == nullptr) return;
    if (LoreDiaryText->GetText().ToString() == LoreDiaryTextToShow.ToString()) return;

    LoreDiaryText->SetVisibility(ESlateVisibility::Visible);
    LoreDiaryText->SetText(LoreDiaryTextToShow);
    
}
void ULoreDiaryMasterWidget::CreateNewButtonComponentEvent(FText LoreDiaryTextToShow,FText LoreDiaryTextName)
{
    ULoreDiaryPageButtonComponent* LoreDiaryPageWidget = CreateWidget<ULoreDiaryPageButtonComponent>(this,LoreDiaryButtonClass);
    if (LoreDiaryPageWidget)
    {
        LoreDiaryPageWidget->DiaryPageButtonName = LoreDiaryTextName;
        LoreDiaryPageWidget->DiaryPageButtonLoreText = LoreDiaryTextToShow;
        LoreDiaryPageWidget->OnOpenDiaryPageNotify.AddDynamic(this,&ThisClass::RegisterClickedButtonPage);
        LoreDiaryButtonsContainer->AddChildToVerticalBox(LoreDiaryPageWidget);
        LoreDiaryPageWidget->SetVisibility(ESlateVisibility::Visible);
    }

}
void ULoreDiaryMasterWidget::RegisterClickedButtonPage(ULoreDiaryPageButtonComponent* PageButton)
{
    ShowDiaryPageTextEvent(PageButton->DiaryPageButtonLoreText,PageButton->DiaryPageButtonName);
}


