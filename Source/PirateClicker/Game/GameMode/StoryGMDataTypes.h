#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StoryGMDataTypes.generated.h"

// State Game
UENUM(BlueprintType)
enum class EStateGame : uint8
{
    None,
    Loading,
    InProgress,
    Pause,
    GameWin,
    GameLose,
    Dialog,
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Название волны"))
    FText NameWave{FText::FromString("Name Wave #")};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Задержки перед стартом волны", ClampMin = "1.0", ForceUnits = "s"))
    float DelayForStart = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Массив под волн"))
    TArray<FDataUnderWave> ArrUnderWaves;
};

UENUM(BlueprintType)
enum class ETypeSide : uint8
{
    Player UMETA(DisplayName = "Главный герой"),
    Opponent UMETA(DisplayName = "Оппонент"),
};

USTRUCT(BlueprintType)
struct FDialogData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Сторона"))
    ETypeSide TypeSide{ETypeSide::Player};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Текст"))
    FText DataText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "SoundBase"))
    FSoftObjectPath VoicePath;
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "Texture2D", ToolTip = "Набор изображений"))
    TMap<ETypeSide, FSoftObjectPath> ImageTypeSide{TPair<ETypeSide, FSoftObjectPath>(ETypeSide::Opponent, ""), TPair<ETypeSide, FSoftObjectPath>(ETypeSide::Player, "")};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Диалог при старте игры"))
    TArray<FDialogData> StartGameDialogs;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Диалог при победе"))
    TArray<FDialogData> WinGameDialogs;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Диалог при поражении"))
    TArray<FDialogData> LoseGameDialogs;
};
