// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoryGMDataTypes.h"
#include "GameFramework/GameModeBase.h"
#include "StoryGMBase.generated.h"

class ATotemZoneActor;
class AGoldStorageActor;
class APlayerPawn;
class AGamePC;
class UDataTable;

/**
 *
 */
UENUM(BlueprintType)
enum class EPresetTotems : uint8
{
    Fire,
    Frost,
    ThirdType,
    FourthType,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateGameSignature, const EStateGame&, StateGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRunGameWaveSignature, int32, NumWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeTreasureCountSignature, int32, CountTreasure);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetupTotemPartSignature, const TArray<EPresetTotems>&, ArrayPresetTotems);

/**
 * @class Story GM
 */
UCLASS()
class PIRATECLICKER_API AStoryGMBase : public AGameModeBase
{
    GENERATED_BODY()

#pragma region Default

public:
    AStoryGMBase();

protected:
    virtual void StartPlay() override;

#pragma endregion

#pragma region Action

public:
    /**
     * @public Get state game
     * @return EStateGame
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    FORCEINLINE EStateGame GetStateGame() const { return StateGame; }

    /**
     * @public Change state game
     * @param1 EStateGame
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    void ChangeStateGame(const EStateGame& NewState);

    /**
     * @public Get count waves
     * @return int32
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    int32 GetCountWaves() const { return (GameRule) ? GameRule->ArrWaves.Num() : INDEX_NONE; }

    /**
     * @public Get count waves
     * @return int32
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    FText GetNameWave(const int32 IndexWave) const;

    /**
     * @public Get number to run wave
     * @return int32
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    int32 GetNumRunWave() const { return TargetIndexWave; }

    /**
     * @public Get count gold on Level
     * @return int32
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    int32 GetCountGoldOnLevel() const;

    /**
     * @public Get pawn player
     * @return APlayerPawn*
     **/
    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    APlayerPawn* GetPlayerPawn() const { return PlayerPawn; }

    UFUNCTION(BlueprintCallable, Category = "AStoryGMBase | Action")
    const TArray<ATotemZoneActor*>& GetArrayTotemZone() const { return ArrayTotem; }

private:
    /**
     * @public Run waves
     * @param1 int32
     **/
    void RunWaves(int32 IndexWave);

    /**
     * @public Run under waves
     * @param1 FDataGameWave
     **/
    void RunUnderWaves(FDataGameWave DataGameWave);

    /**
     * @public Registration of the spawner shutdown event
     * @param1 ASpawnerNPC
     **/
    UFUNCTION()
    void RegisterCompleteWorkSpawner(ASpawnerNPC* SpawnerNPC);

    /**
     * @public Complete the gameplay and summarize the game
     * @param1 int32
     **/
    void CompleteGameProcess();

    /**
     **/
    UFUNCTION()
    void ReduceCountTreasure();

#pragma endregion

#pragma region DataGameMode

private:
    // @private Data table for game rule
    UPROPERTY()
    UDataTable* GameRuleDataTable{nullptr};

    // @private Current game rule struct
    FGameRule* GameRule{nullptr};

    // @private Current game player controller
    UPROPERTY()
    AGamePC* GamePC{nullptr};

    // @private Current player pawn
    UPROPERTY()
    APlayerPawn* PlayerPawn{nullptr};

    // @private Current state game
    EStateGame StateGame = EStateGame::Loading;

    int32 TargetIndexWave{0};

    // @private Storing the status of NPC spawners
    TMap<ASpawnerNPC*, bool> StatusSpawners;

    // @private Storing the status of NPC spawners
    TArray<AGoldStorageActor*> ArrayGoldStorage;

    TArray<ATotemZoneActor*> ArrayTotem;

    int32 AllCountTreasure{0};

#pragma endregion

#pragma region Signature

public:
    UPROPERTY(BlueprintAssignable)
    FChangeStateGameSignature OnChangeStateGame;

    UPROPERTY(BlueprintAssignable)
    FRunGameWaveSignature OnRunGameWave;

    UPROPERTY(BlueprintAssignable)
    FChangeTreasureCountSignature OnChangeTreasureCount;

    UPROPERTY(BlueprintAssignable)
    FSetupTotemPartSignature OnSetupTotemPart;

#pragma endregion
};
