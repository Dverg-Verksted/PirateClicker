// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Game/AI/AIDataTypes.h"
#include "Components/ActorComponent.h"
#include "Library/LibraryDataTypes.h"
#include "MoveComponent.generated.h"

class ASplineActor;
class USplineComponent;

#define LOG_MOVE(LogVerb, Text) Print_LogMovement(LogVerb, Text, __LINE__, __FUNCTION__)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopedMoveSignature);

/**
 * @class Component for movement pirate
 **/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PIRATECLICKER_API UMoveComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this component's properties
    UMoveComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /**
     * @public Initializing parameters for move component
     * @param1 FDataPirate
     **/
    UFUNCTION(BlueprintCallable, Category = "APirateActorBase | Default")
    void InitMoveData(const float SpeedMove, const float SpeedRotate);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    /**
     * @public Write a log
     **/
    void Print_LogMovement(const ELogVerb LogVerb, const FString Text, const int Line, const char* Function) const;

#pragma endregion

#pragma region Action

public:

    /**
     * @public Go move to spline
     **/
    void GoMove(const FMovementData& MovementData);

    /**
     * @public Stop movement
     **/
    UFUNCTION(BlueprintCallable)
    void StopMovement();

    /**
     * @public Setup value in percent on speed move by default
     * @param1 float
     **/
    UFUNCTION(BlueprintCallable)
    void SetupSpeedModifyToPercent(const float SpeedPercent);

    /**
     * @public Reset value in percent on speed move by default=
     **/
    UFUNCTION(BlueprintCallable)
    void ResetSpeedModifyToPercent();

#pragma endregion

#pragma region DataMove

protected:
    
    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement", meta = (ToolTip = "Скорость передвижения пирата", ClampMin = "1.0", ClampMax = "1500.0", ForceUnits = "m/s"))
    float DefaultSpeedMove{10.0f};

    // Rotate speed pirate
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement", meta = (ToolTip = "Скорость поворота пирата", ClampMin = "0.1", ClampMax = "5.0", ForceUnits = "x"))
    float DefaultSpeedRotate{0.1f};

    // Speed modify
    float SpeedModify{1.0f};
private:

    EStateMovement StateMovement = EStateMovement::Stop;

    // Target data for movement
    FMovementData TargetData;

    /**
     * @private Move to Spline
     **/
    void MoveToSpline(float DeltaTime);

#pragma endregion

#pragma region Signature

public:
    UPROPERTY(BlueprintAssignable)
    FStopedMoveSignature OnStopedMove;

#pragma endregion
};
