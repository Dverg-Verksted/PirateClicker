// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuHUD.h"
#include "Library/PirateClickerLibrary.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (!CHECKED(StartWidget.GetDefaultObject() != nullptr, "StartWidget is nullptr"))return;
    if (!CHECKED(SettingsWidget.GetDefaultObject() != nullptr, "SettingsWidget is nullptr"))return;
    if (!CHECKED(ShopWidget.GetDefaultObject() != nullptr, "ShopWidget is nullptr"))return;
    if (!CHECKED(LevelSelectWidget.GetDefaultObject() != nullptr, "ShopWidget is nullptr"))return;
    if (!CHECKED(LoreDiaryWidget.GetDefaultObject() != nullptr, "LoreDiaryWidget is nullptr"))return;

    SetStateMenuWidgets.Add(EStateMenuMode::MainMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),StartWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::SettingsMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),SettingsWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::ShopMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),ShopWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::LevelSelectMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),LevelSelectWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::LoreDairyMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),LoreDiaryWidget));
    
    for (const auto& Pair:SetStateMenuWidgets)
    {
        Pair.Value->AddToViewport();
        Pair.Value->SetVisibility(ESlateVisibility::Collapsed);
    }

    
    AMenuGameMode* MenuGameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (MenuGameMode)
    {
        MenuGameMode->OnChangeMenuStateNotify.AddDynamic(this,&ThisClass::RegisterChangeMenuState);
    }
}

    void AMenuHUD::RegisterChangeMenuState(EStateMenuMode NewMenuState)
{
        
    if (SetStateMenuWidgets.Contains(NewMenuState))
    {
        if (CurrentVisibleWidget)
        {
            CurrentVisibleWidget->SetVisibility(ESlateVisibility::Hidden);
        }
        CurrentVisibleWidget = SetStateMenuWidgets[NewMenuState];
        CurrentVisibleWidget ->SetVisibility(ESlateVisibility::Visible);
    }
}
