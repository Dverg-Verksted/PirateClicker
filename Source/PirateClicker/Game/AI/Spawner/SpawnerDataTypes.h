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
};
