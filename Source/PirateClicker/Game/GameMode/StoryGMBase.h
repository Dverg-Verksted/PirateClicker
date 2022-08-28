// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoryGMDataTypes.h"
#include "GameFramework/GameModeBase.h"
#include "StoryGMBase.generated.h"

class APlayerPawn;
class AGamePC;
class UDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateGameSignature, const EStateGame&, StateGame);

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
    
private:
    
    void RunWaves(int32 IndexWave);
    void RunUnderWaves(FDataGameWave DataGameWave);

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

#pragma endregion

#pragma region Signature

public:

    UPROPERTY(BlueprintAssignable)
    FChangeStateGameSignature OnChangeStateGame;

#pragma endregion 
    
};
