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
}
void ULoreDiaryMasterWidget::ShowDiaryPageTextEvent(FText LoreDiaryTextToShow,FText LoreDiaryTextName)
{
    if (LoreDiaryText == nullptr) return;
    if (!LoreDiaryText->IsVisible())
    {
        LoreDiaryText->SetVisibility(ESlateVisibility::Visible);
        LoreDiaryText->SetText(LoreDiaryTextToShow);
    }
}
void ULoreDiaryMasterWidget::CreateNewButtonComponentEvent()
{
    UWidget* LoreDiaryPageWidget = CreateWidget<ULoreDiaryPageButtonComponent>(this,LoreDiaryButtonClass);
    LoreDiaryButtonsContainer->AddChildToVerticalBox(LoreDiaryPageWidget);
    LoreDiaryPageWidget->SetVisibility(ESlateVisibility::Collapsed);
}


