// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryGMBase.h"

#include "StoryGMLibrary.h"
#include "Engine/DataTable.h"
#include "Game/AI/Spawner/SpawnerNPC.h"
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

    if (!CHECKED(GameRuleDataTable != nullptr, "Game rule data table is nullptr")) return;

    const FName NameGameRule = UStoryGMLibrary::FindRowNameGameRule(GameRuleDataTable, GetWorld()->GetName());
    if (!CHECKED(NameGameRule != NAME_None, "World row name is not found")) return;

    LOG_PIRATE(ELogRSVerb::Display, FString::Printf(TEXT("Current row name: [%s]"), *(NameGameRule.ToString())));
    GameRule = GameRuleDataTable->FindRow<FGameRule>(NameGameRule, "");

    const TArray<FDataGameWave>& ArrayWaves = GameRule->ArrWaves;
    if (!UStoryGMLibrary::CheckArrayWaves(ArrayWaves)) return;

    RunWaves(0);
}

#pragma endregion

#pragma region Action

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
