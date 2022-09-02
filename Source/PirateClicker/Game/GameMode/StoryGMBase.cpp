// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryGMBase.h"
#include "StoryGMLibrary.h"
#include "Algo/Accumulate.h"
#include "Engine/DataTable.h"
#include "Game/AI/Spawner/SpawnerNPC.h"
#include "Game/GoldStorage/GoldStorageActor.h"
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

    UPirateClickerLibrary::FindAllActors(GetWorld(), ArrayGoldStorage);
    if (!CHECKED(ArrayGoldStorage.Num() != 0, "Array gold storage is empty and equal ZERO")) return;

    GamePC = Cast<AGamePC>(GetWorld()->GetFirstPlayerController());
    if (!CHECKED(GamePC != nullptr, "GamePC is nullptr")) return;

    UPirateClickerLibrary::FindActor(GetWorld(), PlayerPawn);
    if (!CHECKED(PlayerPawn != nullptr, "Player Pawne is nullptr")) return;

    GamePC->Possess(PlayerPawn);

    if (!CHECKED(GameRuleDataTable != nullptr, "Game rule data table is nullptr")) return;

    const FName NameGameRule = UStoryGMLibrary::FindRowNameGameRule(GameRuleDataTable, GetWorld()->GetName());
    if (!CHECKED(NameGameRule != NAME_None, "World row name is not found")) return;

    LOG_PIRATE(ELogVerb::Display, FString::Printf(TEXT("Current row name: [%s]"), *(NameGameRule.ToString())));
    GameRule = GameRuleDataTable->FindRow<FGameRule>(NameGameRule, "");

    const TArray<FDataGameWave>& ArrayWaves = GameRule->ArrWaves;
    if (!UStoryGMLibrary::CheckArrayWaves(ArrayWaves)) return;

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(
        TimerHandle,
        [&]()
        {
            ChangeStateGame(EStateGame::InProgress);
            TargetIndexWave = 0;
            RunWaves(TargetIndexWave);
        },
        1.0f, false);
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
    StatusSpawners.Empty();
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DataGameWave.DelayForStart, false);
    OnRunGameWave.Broadcast(IndexWave);
}

void AStoryGMBase::RunUnderWaves(FDataGameWave DataGameWave)
{
    const TArray<FDataUnderWave>& ArrayUnderWaves = DataGameWave.ArrUnderWaves;
    for (const FDataUnderWave& UnderWave : ArrayUnderWaves)
    {
        ASpawnerNPC* SpawnerNPC = UnderWave.SoftPtrSpawnerNPC.Get();
        if (!CHECKED(SpawnerNPC != nullptr, "Spawner NPC is nullptr")) continue;
        SpawnerNPC->AddDataSpawn(FDataPirateSpawn(UnderWave.PirateAsset, UnderWave.CountSpawn, UnderWave.NextSpawnUnderWave));
        if (!StatusSpawners.Contains(SpawnerNPC))
        {
            StatusSpawners.Add(SpawnerNPC, false);
            SpawnerNPC->OnCompleteWorkSpawner.AddDynamic(this, &ThisClass::RegisterCompleteWorkSpawner);
        }
    }
}

void AStoryGMBase::RegisterCompleteWorkSpawner(ASpawnerNPC* SpawnerNPC)
{
    if (!CHECKED(SpawnerNPC != nullptr, "Spawner NPC is nullptr")) return;
    if (!CHECKED(StatusSpawners.Contains(SpawnerNPC), FString::Printf(TEXT("SpawnerNPC: [%s] is doesn't content"), *SpawnerNPC->GetName()))) return;
    if (!CHECKED(StatusSpawners[SpawnerNPC] == false, FString::Printf(TEXT("SpawnerNPC: [%s] is already complete"), *SpawnerNPC->GetName()))) return;

    StatusSpawners[SpawnerNPC] = true;
    SpawnerNPC->OnCompleteWorkSpawner.RemoveDynamic(this, &ThisClass::RegisterCompleteWorkSpawner);

    for (const auto& Pair : StatusSpawners)
    {
        if (!Pair.Value) return;
    }

    ++TargetIndexWave;
    const TArray<FDataGameWave>& ArrayWaves = GameRule->ArrWaves;
    if (ArrayWaves.IsValidIndex(TargetIndexWave))
    {
        RunWaves(TargetIndexWave);
    }
    else
    {
        CompleteGameProcess();
    }
}

void AStoryGMBase::CompleteGameProcess()
{
    if (GetCountGoldOnLevel() == 0)
    {
        ChangeStateGame(EStateGame::GameLose);
    }
    else
    {
        ChangeStateGame(EStateGame::GameWin);
    }
}

int32 AStoryGMBase::GetCountGoldOnLevel() const
{
    return Algo::Accumulate(ArrayGoldStorage, 0, [](int32 Result, AGoldStorageActor* Storage) { return Storage ? Result + Storage->GetCurrentGold() : Result; });
}

#pragma endregion
