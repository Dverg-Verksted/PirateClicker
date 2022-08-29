// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS(HideCategories = ("Replication", "Collision", "Input", "Actor", "LOD", "Cooking"))
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

#if WITH_EDITOR

    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

#endif

#pragma endregion

#pragma region Components

public:
    
    /**
     * @public Get root scene component
     * @return USceneComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USceneComponent* GetRootScene() const { return RootScene; }

    /**
     * @public Get Sphere Collision
     * @return USphereComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USphereComponent* GetSphereCollision() const { return SphereCollision; }

    /**
     * @public Get Spring Arm component
     * @return USpringArmComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }

    /**
     * @public Get Camera component
     * @return UCameraComponent*
     **/
    UFUNCTION(BlueprintCallable, Category = "APlayerPawn | Components")
    FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

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

#pragma endregion
    
};
