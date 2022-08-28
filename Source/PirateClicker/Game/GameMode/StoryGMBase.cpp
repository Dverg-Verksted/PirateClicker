// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryGMBase.h"
#include "StoryGMLibrary.h"
#include "Engine/DataTable.h"
#include "Game/AI/Spawner/SpawnerNPC.h"
#include "Game/Player/GamePC.h"
#include "Game/Player/PlayerPawn.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

AStoryGMBase::AStoryGMBase()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> TableObject(TEXT("DataTable'/Game/PirateClicker/Core/GameMode/DT_GameRule.DT_GameRule'"));
    if (TableObject.Succeeded())
    {
        GameRuleDataTable = TableObject.Object;
    }
}

void AStoryGMBase::StartPlay()
{
    Super::StartPlay();

    GamePC = Cast<AGamePC>(GetWorld()->GetFirstPlayerController());
    if (!CHECKED(GamePC != nullptr, "GamePC is nullptr")) return;
    
    UPirateClickerLibrary::FindActor(GetWorld(), PlayerPawn);
    if (!CHECKED(PlayerPawn != nullptr, "Player Pawne is nullptr")) return;

    GamePC->Possess(PlayerPawn);
    
    if (!CHECKED(GameRuleDataTable != nullptr, "Game rule data table is nullptr")) return;

    const FName NameGameRule = UStoryGMLibrary::FindRowNameGameRule(GameRuleDataTable, GetWorld()->GetName());
    if (!CHECKED(NameGameRule != NAME_None, "World row name is not found")) return;

    LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("Current row name: [%s]"), *(NameGameRule.ToString())));
    GameRule = GameRuleDataTable->FindRow<FGameRule>(NameGameRule, "");

    const TArray<FDataGameWave>& ArrayWaves = GameRule->ArrWaves;
    if (!UStoryGMLibrary::CheckArrayWaves(ArrayWaves)) return;

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [&]()
    {
        ChangeStateGame(EStateGame::InProgress);
        RunWaves(0);
    }, 1.0f, false);
}

#pragma endregion

#pragma region Action

void AStoryGMBase::ChangeStateGame(const EStateGame& NewState)
{
    if (!CHECKED(StateGame != NewState, "State game is equal new state")) return;

    StateGame = NewState;
    OnChangeStateGame.Broadcast(StateGame);
}

void AStoryGMBase::RunWaves(int32 IndexWave)
{
    const TArray<FDataGameWave>& ArrayWaves = GameRule->ArrWaves;
    if (!CHECKED(ArrayWaves.IsValidIndex(IndexWave), FString::Printf(TEXT("Index wave: [%i] doesn't valid index wave"), IndexWave))) return;
    const FDataGameWave& DataGameWave = ArrayWaves[IndexWave];

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &ThisClass::RunUnderWaves, DataGameWave);
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DataGameWave.DelayForStart, false);
}

void AStoryGMBase::RunUnderWaves(FDataGameWave DataGameWave)
{
    const TArray<FDataUnderWave>& ArrayUnderWaves = DataGameWave.ArrUnderWaves;
    for (const FDataUnderWave& UnderWave : ArrayUnderWaves)
    {
        ASpawnerNPC* SpawnerNPC = UnderWave.SoftPtrSpawnerNPC.Get();
        if (!CHECKED(SpawnerNPC != nullptr, "Spawner NPC is nullptr")) continue;
        SpawnerNPC->AddDataSpawn(FDataPirateSpawn(UnderWave.PirateAsset, UnderWave.CountSpawn, UnderWave.NextSpawnUnderWave));
    }
}

#pragma endregion
