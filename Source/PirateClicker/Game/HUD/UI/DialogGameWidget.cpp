// This section is the property of the Dverg Verksted team

#include "Game/HUD/UI/DialogGameWidget.h"
#include "Components/Button.h"
#include "Game/GameMode/StoryGMBase.h"

#pragma region Default

void UDialogGameWidget::InitWidget()
{
    Super::InitWidget();

    if (StoryGM->GetPrevStateGame() == EStateGame::Loading)
    {
        NextStateGame = EStateGame::InProgress;
    }
    if (StoryGM->GetPrevStateGame() == EStateGame::GameWin)
    {
        NextStateGame = EStateGame::GameWin;
    }
    if (StoryGM->GetPrevStateGame() == EStateGame::GameLose)
    {
        NextStateGame = EStateGame::GameLose;
    }
    TargetIndexDialog = 0;
    ArrayDataDialogs = StoryGM->GetCurrentStateDataDialogs();
    if (ArrayDataDialogs.Num() == 0)
    {
        CompleteDialog();
    }
    NextPushDataDialog->OnClicked.AddDynamic(this, &ThisClass::PushDataDialog);
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::PushDataDialog);
}

#pragma endregion

#pragma region ActionDialog

void UDialogGameWidget::PushDataDialog()
{
    if (ArrayDataDialogs.Num() == TargetIndexDialog)
    {
        CompleteDialog();
        return;
    }
    PushDataDialog_Event(ArrayDataDialogs[TargetIndexDialog++], ArrayDataDialogs.Num() == TargetIndexDialog);
}

void UDialogGameWidget::CompleteDialog()
{
    NextPushDataDialog->OnClicked.RemoveDynamic(this, &ThisClass::PushDataDialog);
    const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(StoryGM, &AStoryGMBase::ChangeStateGame, NextStateGame);
    GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
}

#pragma endregion
