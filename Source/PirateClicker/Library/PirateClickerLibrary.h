// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "LibraryDataTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EngineUtils.h"
#include "PirateClickerLibrary.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogPirateClicker, All, All);
#define LOG_PIRATE(LogVerb, Text) UPirateClickerLibrary::Print_Log(LogVerb, Text, __LINE__, __FUNCTION__)
#define CHECKED(Cond, Text) UPirateClickerLibrary::CheckedCondition(Cond, Text, __LINE__, __FUNCTION__)

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncAssetLoadSignature, bool, bResult, UObject*, Object);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncSpawnActorSignature, bool, bResult, FStringAssetReference, LoadedReference, AActor*, SpawnedActor);

/**
 * @class Generalized Pirate Clicker Functional Library
 */
UCLASS()
class PIRATECLICKER_API UPirateClickerLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * @public Write a log
     **/
    static void Print_Log(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function);

    /**
     * @public Check the condition
     * @return bool
     **/
    static bool CheckedCondition(const bool bCondition, const FString Text, const int Line, const char* Function);

#pragma region WorldUtils

public:
    UFUNCTION(BlueprintCallable, Category = "PirateClickerLibrary")
    static UWorld* GetWorldInEditor();

    template <typename T>
    static void FindAllActors(UWorld* InWorld, TArray<T*>& OutActors)
    {
        if (!InWorld) return;

        for (TActorIterator<T> Iterator(InWorld); Iterator; ++Iterator)
        {
            OutActors.Add(*Iterator);
        }
    }

    template <typename T>
    static void FindActor(UWorld* InWorld, T*& OutActor)
    {
        if (!InWorld) return;

        for (TActorIterator<T> Iterator(InWorld); Iterator; ++Iterator)
        {
            OutActor = *Iterator;
            return;
        }
    }

    template <typename T>
    static void FindActorByName(UWorld* InWorld, const FString& InActorName, T*& OutActor)
    {
        if (!InWorld || InActorName.IsEmpty()) return;

        for (TActorIterator<T> Iterator(InWorld); Iterator; ++Iterator)
        {
            AActor* LActor = *Iterator;

            if (LActor->GetName() != InActorName) continue;

            OutActor = *Iterator;
            return;
        }
    }

#pragma endregion

#pragma region LoadAssets

public:
    /** Asynchronously load asset */
    UFUNCTION(BlueprintCallable, Category = "PirateClickerLibrary")
    static void AsyncAssetLoadObject(TAssetPtr<UObject> AssetPtr, const FAsyncAssetLoadSignature& Callback);

    /** Asynchronously load asset and spawn actor then */
    UFUNCTION(BlueprintCallable, Category = "PirateClickerLibrary", meta = (WorldContext = "WorldContextObject"))
    static void AsyncSpawnActor(UObject* WorldContextObject, TAssetSubclassOf<AActor> AssetPtr, FTransform SpawnTransform, const FAsyncSpawnActorSignature& Callback);

private:
    /** Called when asset loading is finished */
    UFUNCTION()
    static void OnAsyncAssetLoadObjectComplete(FStringAssetReference Reference, FAsyncAssetLoadSignature Callback);

    /** Called when asset loading for actor spawn is finished */
    static void OnAsyncSpawnActorComplete(UObject* WorldContextObject, FStringAssetReference Reference, FTransform SpawnTransform, FAsyncSpawnActorSignature Callback);

#pragma endregion
};
