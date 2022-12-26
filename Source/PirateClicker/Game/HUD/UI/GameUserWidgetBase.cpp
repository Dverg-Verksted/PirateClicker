// This section is the property of the Dverg Verksted team

#include "Game/HUD/UI/GameUserWidgetBase.h"
#include "Game/GameMode/StoryGMBase.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

void UGameUserWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    StoryGM = Cast<AStoryGMBase>(GetWorld()->GetAuthGameMode());
    if (CHECKED(StoryGM != nullptr, "Story GM is nullptr")) return;
}

#pragma endregion
