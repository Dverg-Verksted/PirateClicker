// This section is the property of the Dverg Verksted team

#include "Library/PirateClickerLibrary.h"

#include "Components/SplineComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Game/AI/Spawner/SplineActor.h"

void UPirateClickerLibrary::Print_Log(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function)
{
    if (LogVerb == ELogVerb::Display)
    {
        UE_LOG(LogPirateClicker, Display, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
    else if (LogVerb == ELogVerb::Warning)
    {
        UE_LOG(LogPirateClicker, Warning, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
    else if (LogVerb == ELogVerb::Error)
    {
        UE_LOG(LogPirateClicker, Error, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
}

bool UPirateClickerLibrary::CheckedCondition(const bool bCondition, const FString Text, const int Line, const char* Function)
{
    if (!bCondition)
    {
        Print_Log(ELogVerb::Error, Text, Line, Function);
        return false;
    }
    return true;
}

#pragma region Action

int32 UPirateClickerLibrary::GetIndexAlongDistTargetPosition(const ASplineActor* Spline, const FVector& TargetPosition)
{
    if (!Spline) return INDEX_NONE;

    TMap<int32, float> TempContains;
    const int32 Numbers = Spline->GetSpline()->GetNumberOfSplinePoints();
    for (int32 i = 0; i < Numbers; ++i)
    {
        float Dist = FVector::Dist(TargetPosition, Spline->GetSpline()->GetWorldLocationAtSplinePoint(i));
        TempContains.Add(i, Dist);
    }

    float Distance = MAX_FLT;
    int32 TempTargetIndex = INDEX_NONE;
    for (const auto& Pair : TempContains)
    {
        if (Pair.Value < Distance)
        {
            Distance = Pair.Value;
            TempTargetIndex = Pair.Key;
        }
    }

    return TempTargetIndex;
}

#pragma endregion

#pragma region WorldUtils

UWorld* UPirateClickerLibrary::GetWorldInEditor()
{
    TIndirectArray<FWorldContext> LWorlds = GEngine->GetWorldContexts();

    for (FWorldContext LWorld : LWorlds)
    {
        if (LWorld.WorldType == EWorldType::Editor)
        {
            return LWorld.World();
        }
    }

    return nullptr;
}

#pragma endregion

#pragma region LoadAssets

void UPirateClickerLibrary::AsyncAssetLoadObject(TAssetPtr<UObject> AssetPtr, const FAsyncAssetLoadSignature& Callback)
{
    FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
    const FStringAssetReference Reference = AssetPtr.ToSoftObjectPath();
    AssetLoader.RequestAsyncLoad(Reference, FStreamableDelegate::CreateStatic(&UPirateClickerLibrary::OnAsyncAssetLoadObjectComplete, Reference, Callback));
}

void UPirateClickerLibrary::AsyncSpawnActor(UObject* WorldContextObject, TAssetSubclassOf<AActor> AssetPtr, FTransform SpawnTransform, const FAsyncSpawnActorSignature& Callback)
{
    FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
    const FStringAssetReference L_Reference = AssetPtr.ToSoftObjectPath();
    AssetLoader.RequestAsyncLoad(L_Reference, FStreamableDelegate::CreateStatic(&UPirateClickerLibrary::OnAsyncSpawnActorComplete, WorldContextObject, L_Reference, SpawnTransform, Callback));
}

void UPirateClickerLibrary::OnAsyncAssetLoadObjectComplete(FSoftObjectPath Reference, FAsyncAssetLoadSignature Callback)
{
    UObject* Obj = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, *(Reference.ToString())));
    Callback.ExecuteIfBound(Obj != nullptr, Obj);
}

void UPirateClickerLibrary::OnAsyncSpawnActorComplete(UObject* WorldContextObject, FStringAssetReference Reference, FTransform SpawnTransform, FAsyncSpawnActorSignature Callback)
{
    AActor* SpawnedActor = nullptr;

    // Asset now should be loaded into memory, so try to get it
    UClass* ActorClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *(Reference.ToString())));
    if (ActorClass != nullptr)
    {
        // Spawn actor from asset now
        SpawnedActor = WorldContextObject->GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform);
    }

    Callback.ExecuteIfBound(SpawnedActor != nullptr, Reference, SpawnedActor);
}

#pragma endregion
