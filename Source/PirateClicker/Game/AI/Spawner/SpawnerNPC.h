// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "SpawnerDataTypes.h"
#include "GameFramework/Actor.h"
#include "Library/LibraryDataTypes.h"
#include "SpawnerNPC.generated.h"

class APirateActorBase;
class USphereComponent;

#define LOG_SPAWNER(LogVerb, Text) Print_LogSpawner(LogVerb, Text, __LINE__, __FUNCTION__)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllPirateDeadSignature);

UCLASS(HideCategories = ("Replication", "Collision", "Input", "Actor", "LOD", "Cooking"))
class PIRATECLICKER_API ASpawnerNPC : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this actor's properties
    ASpawnerNPC();

    /**
     *	Function called every frame on this Actor. Override this function to implement custom logic to be executed every frame.
     *	Note that Tick is disabled by default, and you will need to check PrimaryActorTick.bCanEverTick is set to true to enable it.
     *
     *	@param	DeltaSeconds	Game time elapsed during last frame modified by the time dilation
     */
    virtual void Tick(float DeltaSeconds) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
    /**
     * @public Write a log
     **/
    void Print_LogSpawner(const ELogRSVerb LogVerb, const FString Text, const int Line, const char* Function) const;

#pragma endregion

#pragma region Components

protected:
    // @protected Root scene component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // @protected Billboard component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBillboardComponent* Billboard;

    // @protected Sphere Collision
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereCollision;

#pragma endregion

#pragma region Data

protected:
    UPROPERTY(EditInstanceOnly, Category = "Settings SpawnerNPC", meta = (ClampMin = "30.0", ClampMax = "5000.0", ForceUnits = "cm"))
    float RadiusCollision = 100.0f;

    UPROPERTY(EditInstanceOnly, Category = "Settings SpawnerNPC", meta = (ClampMin = "1", ClampMax = "100"))
    int32 CountSpawnPosition = 5;

    UPROPERTY(EditInstanceOnly, Category = "Settings SpawnerNPC", meta = (ToolTip = "Набор указателей на золотохранилище для установки путей"))
    TArray<FDataSplineInfo> ArrDataSplineInfo;

private:
    // @private Array saved position
    TArray<FVector> ArrSavedPosition;

    // @private Array spawn pirates
    TArray<APirateActorBase*> ArrayPirates;

    // @private Pirate Spawn Data Queue
    TQueue<FDataPirateSpawn> QueueDataUnderWaves;

    FTimerHandle TimerHandleSpawnPirate;

#pragma endregion

#pragma region Action

public:
    /**
     * @public Add data to spawn pirate
     * @param1 FDataPirateSpawn
     **/
    UFUNCTION(BlueprintCallable, Category = "ASpawnerNPC | Action")
    void AddDataSpawn(const FDataPirateSpawn& DataPirateSpawn);

private:
    /**
     * @private Checking the spawn queue
     **/
    void CheckedDataUnderWaves();

    /**
     * @private Start the spawn process
     * @param1 FSoftObjectPath
     * @param2 int32
     **/
    void RunSpawnPirate(const FSoftObjectPath& PirateAsset, const int32 CountSpawn);

    /**
     * @private Register pirate on dead
     * @param1 APirateActorBase*
     **/
    UFUNCTION()
    void RegisterPirateDead(APirateActorBase* Pirate);

    /**
     * @private The process of spawning pirates after loading into memory
     **/
    void OnSpawnPirateComplete(const FSoftObjectPath PirateAsset, const int32 CountSpawn);

    /**
     * @private Generate point position spawn
     * @return TArray<FVector>
     **/
    TArray<FVector> GeneratePositionPoint(const int32 CountSpawn) const;

    /**
     * @private Calculation of the spawn position in the collision radius
     * @return FVector - World position
     **/
    FVector CalculateRandomPositionSpawn() const;

    /**
     * @private Get random position from ArrSavedPosition
     * @return FVector
     **/
    FVector GetRandomPositionFromSavePosition();

    /**
     * @private Get random spline from Array FDataSplineInfo
     * @return ASplineActor
     **/
    ASplineActor* GetRandomTargetSpline();

    UFUNCTION(CallInEditor, Category = "Settings SpawnerNPC")
    void CompileSpline();

    UFUNCTION(CallInEditor, Category = "Settings SpawnerNPC")
    void RemoveAllSpline();

#pragma endregion

#pragma region Signature

public:
    UPROPERTY(BlueprintAssignable)
    FAllPirateDeadSignature OnAllPirateDead;

#pragma endregion
};
