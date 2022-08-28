#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StoryGMDataTypes.generated.h"

// State Game
UENUM(BlueprintType)
enum class EStateGame : uint8
{
    Loading,
    InProgress,
    Pause,
    GameWin,
    GameLose,
};

class ASpawnerNPC;

// Under wave
USTRUCT(BlueprintType)
struct FDataUnderWave
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Указатель на спаунер куда спаунить"))
    TSoftObjectPtr<ASpawnerNPC> SoftPtrSpawnerNPC;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Указатель на ассет пирата", AllowedClasses = "PirateDataAsset"))
    FSoftObjectPath PirateAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Количество сколько нужно заспаунить", ClampMin = "1"))
    int32 CountSpawn = 5;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Задержки после спауна партии", ClampMin = "1.0", ForceUnits = "s"))
    float NextSpawnUnderWave = 1.0f;

    FString ToString() const
    {
        return FString::Printf(TEXT("Spawner NPC: [%s] | Pirate Asset: [%s] | Count spawn: [%i] | Next spawn delay: [%f]"), *this->SoftPtrSpawnerNPC.ToString(), *this->PirateAsset.ToString(),
            this->CountSpawn, this->NextSpawnUnderWave);
    }
};

// Data game wave
USTRUCT(BlueprintType)
struct FDataGameWave
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Задержки перед стартом волны", ClampMin = "1.0", ForceUnits = "s"))
    float DelayForStart = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Массив под волн"))
    TArray<FDataUnderWave> ArrUnderWaves;
};

// Game rule for gamemode
USTRUCT(BlueprintType)
struct FGameRule : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Имя острова"))
    FText NameIsland{FText::FromString("Name Island")};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Имя острова"))
    FText DescriptionIsland{FText::FromString("Description Island")};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World", ToolTip = "Укажите мир в котором будут работать правила"))
    FSoftObjectPath World;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Добавьте и опишите волны"))
    TArray<FDataGameWave> ArrWaves;
};
