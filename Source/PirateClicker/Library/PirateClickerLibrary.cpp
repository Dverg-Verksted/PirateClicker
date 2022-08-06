// This section is the property of the Dverg Verksted team

#include "Library/PirateClickerLibrary.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UPirateClickerLibrary::Print_Log(const ELogRSVerb LogVerb, const FString Text, const int Line, const char* Function)
{
    if (LogVerb == ELogRSVerb::Display)
    {
        UE_LOG(LogPirateClicker, Display, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
    else if (LogVerb == ELogRSVerb::Warning)
    {
        UE_LOG(LogPirateClicker, Warning, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
    else if (LogVerb == ELogRSVerb::Error)
    {
        UE_LOG(LogPirateClicker, Error, TEXT("[%s][%d] TEXT:[%s]"), ANSI_TO_TCHAR(Function), Line, *Text);
    }
}

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

void UPirateClickerLibrary::OnAsyncAssetLoadObjectComplete(FStringAssetReference Reference, FAsyncAssetLoadSignature Callback)
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
