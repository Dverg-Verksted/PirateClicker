// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnDataTypes.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UENUM()
enum class EStateMoveCamera : uint8
{
    Stop,
    Right,
    Left
};

UCLASS(HideCategories = ("Replication", "Collision", "Input", "Actor", "LOD", "Cooking", "Pawn", "Camera", "HLOD", "Physics", "Networking"))
class PIRATECLICKER_API APlayerPawn : public APawn
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this pawn's properties
    APlayerPawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     *	Function called every frame on this Actor. Override this function to implement custom logic to be executed every frame.
     *	Note that Tick is disabled by default, and you will need to check PrimaryActorTick.bCanEverTick is set to true to enable it.
     *
     *	@param	DeltaSeconds	Game time elapsed during last frame modified by the time dilation
     */
    virtual void Tick(float DeltaSeconds) override;

#if WITH_EDITOR

    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

#endif

#pragma endregion

#pragma region Action

    UFUNCTION(BlueprintCallable)
    void ChangeStateCameraMove(ECameraPawnMoved NewState);

private:

    void CalculateDataBoundInfo(FDataInfoBound* Data, const FVector& RelPosBound) const;

#pragma endregion

#pragma region Components

public:
    /**
     * @public Get root scene component
     * @return USceneComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USceneComponent* GetRootScene() const
    {
        return RootScene;
    }

    /**
     * @public Get Sphere Collision
     * @return USphereComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USphereComponent* GetSphereCollision() const
    {
        return SphereCollision;
    }

    /**
     * @public Get Spring Arm component
     * @return USpringArmComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USpringArmComponent* GetSpringArm() const
    {
        return SpringArm;
    }

    /**
     * @public Get Camera component
     * @return UCameraComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE UCameraComponent* GetCamera() const
    {
        return Camera;
    }

private:
    // @private Root scene component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* RootScene{nullptr};

    // @private Sphere Collision
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USphereComponent* SphereCollision{nullptr};

    // @private Spring Arm component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USpringArmComponent* SpringArm{nullptr};

    // @private Spring Arm component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UCameraComponent* Camera{nullptr};

#pragma endregion

#pragma region DataPlayerPawn

private:
    // @private Camera distance
    UPROPERTY(EditInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Дистанция камеры", ClampMin = "30.0"))
    float CameraDistance{300.0f};

    // @private Rotation
    UPROPERTY(EditInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Поворот камеры"))
    FRotator RotatePawn{FRotator::ZeroRotator};

    // @private Speed rotate camera
    UPROPERTY(EditInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Скорость поворота камеры", ClampMin = "1.0"))
    float SpeedRotate{0.0f};

    // @private Left position Bound
    UPROPERTY(EditInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Левая граница перемещение камеры", MakeEditWidget = true))
    FVector LeftBound{FVector(0.0f, -100.0f, 0.0f)};

    UPROPERTY(VisibleInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Инфа об левой границе"))
    FDataInfoBound LeftBoundInfo;

    // @private Right position Bound
    UPROPERTY(EditInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Правая граница перемещение камеры", MakeEditWidget = true))
    FVector RightBound{FVector(0.0f, 100.0f, 0.0f)};

    UPROPERTY(VisibleInstanceOnly, Category = "Settings player pawn", meta = (DisplayName = "Инфа об правой границе"))
    FDataInfoBound RightBoundInfo;

    // @private Speed interp to target position
    UPROPERTY(EditAnywhere, Category = "Settings player pawn", meta = (DisplayName = "Скорость интерполяции камеры до позиции"))
    float SpeedMovedBounds{5.0f};

    UPROPERTY(EditAnywhere, Category = "Settings player pawn", meta = (DisplayName = "Дистанция остановы при интерполяции"))
    float DistOffsetBreak{0.05f};

    ECameraPawnMoved CameraPawnMoved{ECameraPawnMoved::InPlace};
    FVector DefaultPosition{FVector::ZeroVector};

#pragma endregion

#pragma region Signature

    UPROPERTY(BlueprintAssignable)
    FChangeStateCameraPawnMovedSignature OnChangeStateCameraPawnMoved;

#pragma endregion
    
};
