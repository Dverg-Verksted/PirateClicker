// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineActor.generated.h"

class USplineComponent;

UCLASS(HideCategories = ("Replication", "Collision", "Input", "Actor", "LOD", "Cooking"))
class PIRATECLICKER_API ASplineActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASplineActor();

    UFUNCTION(BlueprintCallable, Category = "ASplineActor | GetData")
    FORCEINLINE USplineComponent* GetSpline() const { return Spline; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USplineComponent* Spline;
};
