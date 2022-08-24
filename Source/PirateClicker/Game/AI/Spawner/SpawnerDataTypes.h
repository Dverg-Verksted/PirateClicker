#pragma once

#include "CoreMinimal.h"
#include "SpawnerDataTypes.generated.h"

class ASplineActor;
class AGoldStorageActor;

// Data spline info for GoldStorage
USTRUCT(BlueprintType)
struct FDataSplineInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<AGoldStorageActor> TargetGoldStorage;

    UPROPERTY(EditAnywhere)
    TArray<ASplineActor*> SplineActors;

    UPROPERTY(VisibleAnywhere, meta = (ForceUnits = "cm"))
    float Distance{0.0f};

    ASplineActor* GetRandomSplineActor()
    {
        return this->SplineActors[FMath::RandRange(0, SplineActors.Num() - 1)];
    }
};

USTRUCT(BlueprintType)
struct FDataPirateSpawn
{
    GENERATED_BODY()

    // Asset path to the pirate asset
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FSoftObjectPath PirateAsset{""};

    // Count spawn pirate
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 CountSpawn{0};

    // Delay to spawn pirate
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float DelayTimeSpawn{0.1f};

    FDataPirateSpawn(){}
    FDataPirateSpawn(const FSoftObjectPath& NewPirateAsset, const int32 NewCountSpawn, const float NewDelayTimeSpawn): PirateAsset(NewPirateAsset),
    CountSpawn(NewCountSpawn), DelayTimeSpawn(NewDelayTimeSpawn)
    {}
    FDataPirateSpawn(const FDataPirateSpawn& Other)
    {
        *this = Other;
    }
    void operator=(const FDataPirateSpawn& Other)
    {
        this->PirateAsset = Other.PirateAsset;
        this->CountSpawn = Other.CountSpawn;
        this->DelayTimeSpawn = Other.DelayTimeSpawn;
    }

    FString ToString() const
    {
        return FString::Printf(TEXT("PirateAsset: [%s] | CountSpawn: [%i] | Delay time: [%f]"),
            *PirateAsset.ToString(), CountSpawn, DelayTimeSpawn);
    }
    
};
