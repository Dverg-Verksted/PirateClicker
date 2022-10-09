// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AIDataTypes.h"
#include "Components/ActorComponent.h"
#include "Library/LibraryDataTypes.h"
#include "MovePirateComponent.generated.h"

class ASplineActor;
class USplineComponent;

#define LOG_MOVE(LogVerb, Text) Print_LogMovement(LogVerb, Text, __LINE__, __FUNCTION__)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopedMoveSignature);

/**
 * @class Component for movement pirate
 **/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PIRATECLICKER_API UMovePirateComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this component's properties
    UMovePirateComponent();

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

#pragma region DataMove

public:
    /**
     * @public Go to movement position for AI
     * @param1 FVector
     **/
    void GoAIMoveAdvance(const FVector& ToPos, ASplineActor* SplineActor, const float Duration, const bool bReverse = false);

    /**
     * @public Go to movement position for AI
     * @param1 FVector
     **/
    UFUNCTION(BlueprintCallable)
    void GoAIMove(const FVector& ToPos);

    /**
     * @public run movement
     * @param1 FMovementData
     * @return bool
     **/
    bool RunMovement(const FMovementData& NewData);

    /**
     * @public Stop movement
     **/
    UFUNCTION(BlueprintCallable)
    void StopMovement();

protected:
    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement", meta = (ToolTip = "Скорость передвижения пирата", ClampMin = "1.0", ClampMax = "1500.0", ForceUnits = "m/s"))
    float DefaultSpeedMove{10.0f};

    // Rotate speed pirate
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement", meta = (ToolTip = "Скорость поворота пирата", ClampMin = "0.1", ClampMax = "5.0", ForceUnits = "x"))
    float DefaultSpeedRotate{0.1f};

private:
    EStateMovement StateMovement = EStateMovement::Off;

    // Target data for movement
    FMovementData TargetData;

    // End time
    float EndTime{0.0f};

    /**
     * @private Calculate movement
     **/
    void CalculateMove(float DeltaTime);

    /**
     * @private Calculate rotate
     **/
    void CalculateRotate(float DeltaTime);

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
