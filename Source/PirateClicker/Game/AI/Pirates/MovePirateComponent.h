// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AIDataTypes.h"
#include "Components/ActorComponent.h"
#include "MovePirateComponent.generated.h"

class USplineComponent;

/**
 * @class Component for movement pirate
 **/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATECLICKER_API UMovePirateComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Default
    
public:	
	// Sets default values for this component's properties
	UMovePirateComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#pragma endregion

#pragma region DataMove

public:

    /**
     * @public Setup target spline
     * @param1 USplineComponent*
     **/
    void SetupTargetSpline(USplineComponent* NewSpline) { TargetSpline = NewSpline; }

    /**
     * @public Start move
     * @param1 FVector
     * @return bool
     **/
    bool StartMove(const FMovementData& NewData);

protected:

    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Move",
        meta = (ToolTip = "Скорость пирата", ClampMin = "1.0", ClampMax = "1500.0", ForceUnits = "m/s"))
    float DefaultSpeedMove{10.0f};

private:

    UPROPERTY()
    USplineComponent* TargetSpline;

    UPROPERTY()
    AActor* OwnerPirate;

    // State enable move
    bool bEnableMove{false};

    // end time
    float MoveEndTime{0.0f};

    // Target data for movement
    FMovementData TargetData;

    /**
     * @private Calculate movement
     **/
    void CalculateMove();

    /**
     * @private Calculate rotate
     **/
    void CalculateRotate();

#pragma endregion
    
};
