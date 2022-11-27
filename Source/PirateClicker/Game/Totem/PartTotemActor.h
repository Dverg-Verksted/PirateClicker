// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PartTotemActor.generated.h"

UENUM()
enum class EStatePartTotemAnim
{
    Start,
    Normal,
    End,
};

UCLASS(NotBlueprintable, NotBlueprintType)
class PIRATECLICKER_API APartTotemActor : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this actor's properties
    APartTotemActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

#pragma endregion

#pragma region Components

public:
    /**
     * @public Get root scene component
     * @return USceneComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "Components")
    FORCEINLINE USceneComponent* GetRootScene() const
    {
        return RootScene;
    }

    /**
     * @public Get mesh part totem
     * @return UStaticMeshComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "Components")
    FORCEINLINE UStaticMeshComponent* GetMeshPartTotem() const
    {
        return MeshPartTotem;
    }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* RootScene{nullptr};

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UStaticMeshComponent* MeshPartTotem{nullptr};

#pragma endregion

#pragma region DataPartTotem

private:
    FTimeline StartAnimRotateTimeLine;
    FTimeline StartAnimScaledTimeLine;
    FTimeline NormalAnimRotateTimeLine;
    FTimeline NormalAnimPosTimeLine;
    EStatePartTotemAnim StatePartTotemAnim{EStatePartTotemAnim::Start};

    UPROPERTY(EditDefaultsOnly, Category = "Settings Part Totem")
    UCurveFloat* StartAnimRotateCurve{nullptr};

    UPROPERTY(EditDefaultsOnly, Category = "Settings Part Totem")
    UCurveFloat* StartAnimScaledCurve{nullptr};

    UPROPERTY(EditDefaultsOnly, Category = "Settings Part Totem")
    UCurveFloat* NormalAnimRotateCurve{nullptr};

    UPROPERTY(EditDefaultsOnly, Category = "Settings Part Totem")
    UCurveFloat* NormalAnimPosCurve{nullptr};

    FVector DefaultActorPosition{FVector::ZeroVector};

#pragma endregion

private:
    UFUNCTION()
    void UpdateAnimScaled(float Value);

    UFUNCTION()
    void UpdateAnimRotate(float Value);

    UFUNCTION()
    void UpdateAnimPos(float Value);

    UFUNCTION()
    void FinishAnimRotate();
};
