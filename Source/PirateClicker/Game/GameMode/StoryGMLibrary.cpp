// This section is the property of the Dverg Verksted team

#include "Game/GameMode/StoryGMLibrary.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Checked

bool UStoryGMLibrary::CheckArrayWaves(const TArray<FDataGameWave>& ArrayWaves)
{
    if (!CHECKED(ArrayWaves.Num() != 0, "Array waves is empty")) return false;
    for (const FDataGameWave& Wave : ArrayWaves)
    {
        const TArray<FDataUnderWave>& ArrayUnderWaves = Wave.ArrUnderWaves;
        if (!CHECKED(ArrayUnderWaves.Num() != 0, "Array under waves is empty")) return false;
        for (const FDataUnderWave& UnderWave : ArrayUnderWaves)
        {
            if (!CHECKED(!UnderWave.PirateAsset.IsNull(), "Pirate asset is nullptr")) return false;
            if (!CHECKED(!UnderWave.SoftPtrSpawnerNPC.IsNull(), "Spawner NPC is nullptr")) return false;
        }
    }
    return true;
}

#pragma endregion

#pragma region FindData

FName UStoryGMLibrary::FindRowNameGameRule(UDataTable* Table, const FString& NameWorld)
{
    if (!CHECKED(Table != nullptr, "Data table is nullptr")) return NAME_None;

    TArray<FName> ArrRowName = Table->GetRowNames();
    const auto FindElem = ArrRowName.FindByPredicate(
        [Table, NameWorld](const FName& Row)
        {
            const FGameRule* Rule = Table->FindRow<FGameRule>(Row, "");
            if (!Rule) return false;
            return Rule->World.GetAssetName() == NameWorld;
        });

    return FindElem ? *FindElem : NAME_None;
}

#pragma endregion
