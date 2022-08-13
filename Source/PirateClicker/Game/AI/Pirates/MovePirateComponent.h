// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "AIDataTypes.h"
#include "Components/ActorComponent.h"
#include "Library/LibraryDataTypes.h"
#include "MovePirateComponent.generated.h"

class USplineComponent;

UENUM()
enum class EStateMovement: uint8
{
    Off,
    Rotating,
    Moving
};

#define LOG_MOVE(LogVerb, Text) Print_LogMovement(LogVerb, Text, __LINE__, __FUNCTION__)

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

private:
    
    /**
     * @public Write a log
    **/
    void Print_LogMovement(const ELogRSVerb LogVerb, const FString Text, const int Line, const char* Function) const;

#pragma endregion

#pragma region DataMove

public:

    UFUNCTION(BlueprintCallable)
    void GoAIMove(const FVector& ToPos);
    
    /**
     * @public run movement
     * @param1 FMovementData
     * @return bool
     **/
    bool RunMovement(const FMovementData& NewData);

protected:

    // Movement speed pirate cm/sec
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement",
        meta = (ToolTip = "Скорость передвижения пирата", ClampMin = "1.0", ClampMax = "1500.0", ForceUnits = "m/s"))
    float DefaultSpeedMove{10.0f};

    // Rotate speed pirate 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings Movement",
        meta = (ToolTip = "Скорость поворота пирата", ClampMin = "0.1", ClampMax = "5.0", ForceUnits = "x"))
    float DefaultSpeedRotate{0.1f};

private:

    UPROPERTY()
    AActor* OwnerPirate;

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

#pragma endregion
    
};
