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

USTRUCT()
struct FDataSpawn
{
    GENERATED_BODY()
    
};
