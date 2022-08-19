// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoryGMDataTypes.h"
#include "GameFramework/GameModeBase.h"
#include "StoryGMBase.generated.h"

class UDataTable;

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

#pragma region DataGameMode

private:

    UPROPERTY()
    UDataTable* GameRuleDataTable;

    FGameRule* GameRule;

#pragma endregion

#pragma region Action

private:

    void RunWaves(int32 IndexWave);
    void RunUnderWaves(FDataGameWave DataGameWave);

#pragma endregion
    
};
