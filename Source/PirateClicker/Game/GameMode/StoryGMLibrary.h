// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "StoryGMDataTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StoryGMLibrary.generated.h"

/**
 * @class Story game mode library
 */
UCLASS()
class PIRATECLICKER_API UStoryGMLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region Checked
    
public:

    /**
     * @public Checks the validity of data on waves
     * @param1 TArray<FDataGameWave>
     **/
    UFUNCTION(BlueprintCallable)
    static bool CheckArrayWaves(const TArray<FDataGameWave>& ArrayWaves);

#pragma endregion

#pragma region FindData

public:

    /**
     * @public Checks the validity of data on waves
     * @param1 UDataTable
     * @return FName
     **/
    UFUNCTION(BlueprintCallable)
    static FName FindRowNameGameRule(UDataTable* Table, const FString& NameWorld);

#pragma endregion
};
