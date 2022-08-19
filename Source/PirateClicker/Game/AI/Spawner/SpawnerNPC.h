// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "SpawnerDataTypes.h"
#include "GameFramework/Actor.h"
#include "Library/LibraryDataTypes.h"
#include "SpawnerNPC.generated.h"

class USphereComponent;

#define LOG_SPAWNER(LogVerb, Text) Print_LogSpawner(LogVerb, Text, __LINE__, __FUNCTION__)

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

    UPROPERTY(EditInstanceOnly,  Category = "Settings SpawnerNPC", meta = (ToolTip = "Набор указателей на золотохранилище для установки путей"))
    TArray<FDataSplineInfo> ArrDataSplineInfo;

private:
    TArray<FVector> ArrSavedPosition;

#pragma endregion

#pragma region Action

public:

    void RunSpawnPirate(const FSoftObjectPath& PirateAsset, const int32 CountSpawn);
    
private:
    /**
     * @private Generate point position spawn
     * @return TArray<FVector>
     **/
    TArray<FVector> GeneratePositionPoint() const;

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

    UFUNCTION(CallInEditor, Category = "Settings SpawnerNPC")
    void CompileSpline();

    UFUNCTION(CallInEditor, Category = "Settings SpawnerNPC")
    void RemoveAllSpline();

#pragma endregion
};
