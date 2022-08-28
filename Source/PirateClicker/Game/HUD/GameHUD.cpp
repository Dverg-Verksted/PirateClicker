// This section is the property of the Dverg Verksted team

#include "Game/HUD/GameHUD.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_HUD(TEXT("Pirate.ShowDebugHUD"), false, TEXT("Enable the display of debag information on HUD from canvas panel"), ECVF_Cheat);
#endif

AGameHUD::AGameHUD()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_HUD.GetValueOnGameThread() && StoryGM)
    {
        // AddText(TEXT("Test function AddText"), FText::FromString("This AddText"));
        // AddFloat(TEXT("Test function AddFloat"), 1.488f);
        // AddInt(TEXT("Test function AddInt"), 228);
        // AddBool(TEXT("Test function AddBool"), false);
        // AddBool(TEXT("Test function AddBool"), true);

        AddText(TEXT("---| Story Game mode |---"), FText());
        AddText(TEXT("State game:"), FText::FromString(UEnum::GetValueAsString(StoryGM->GetStateGame())));
    }
#endif
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    StoryGM = Cast<AStoryGMBase>(GetWorld()->GetAuthGameMode());
    if (!CHECKED(StoryGM != nullptr, "Story game mode is nullptr")) return;
}
