// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuHUD.h"
#include "Library/PirateClickerLibrary.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (!CHECKED(StartWidget != nullptr, "StartWidget is nullptr"))return;
    if (!CHECKED(SettingsWidget != nullptr, "SettingsWidget is nullptr"))return;
    if (!CHECKED(ShopWidget != nullptr, "ShopWidget is nullptr"))return;

    SetStateMenuWidgets.Add(EStateMenuMode::MainMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),StartWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::SettingsMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),SettingsWidget));
    SetStateMenuWidgets.Add(EStateMenuMode::ShopMenu,CreateWidget<UMenuMasterWidget>(GetWorld()->GetFirstPlayerController(),ShopWidget));

    AMenuGameMode* MenuGameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (MenuGameMode)
    {
        MenuGameMode->OnChangeMenuStateNotify.AddDynamic(this,&ThisClass::RegisterChangeMenuState);
    }
}

    void AMenuHUD::RegisterChangeMenuState(EStateMenuMode NewMenuState)
{
    if (!CHECKED(CurrentVisibleWidget!= nullptr, "CurrentVisibleWidget is nullptr"))return;
        
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
