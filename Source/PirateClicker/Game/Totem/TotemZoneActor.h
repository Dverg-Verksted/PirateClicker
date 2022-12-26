// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TotemZoneActor.generated.h"

class APartTotemActor;
class UTotemDataAsset;
class USphereComponent;

USTRUCT()
struct FDataSlotTotem
{
    GENERATED_BODY()

    FVector SlotPosition{FVector::ZeroVector};

    UPROPERTY()
    APartTotemActor* TotemActor{nullptr};

    UPROPERTY()
    UTotemDataAsset* TotemDA{nullptr};

    bool IsFreeSlot() const { return TotemActor == nullptr; }
};

UCLASS(HideCategories = ("Replication", "Collision", "Input", "Actor", "LOD", "Cooking"))
class PIRATECLICKER_API ATotemZoneActor : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this actor's properties
    ATotemZoneActor();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UFUNCTION(CallInEditor, Category = "Settings Data Totem")
    void DrawDebugTotem();

    UFUNCTION(CallInEditor, Category = "Settings Data Totem")
    void ClearDebugTotem();

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

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
     * @public Get sphere attack collision
     * @return USphereComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "Components")
    FORCEINLINE USphereComponent* GetSphereCollision() const
    {
        return SphereAttackCollision;
    }

private:
    // @private Root scene component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* RootScene{nullptr};

    // @private sphere attack collision component
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USphereComponent* SphereAttackCollision{nullptr};

#pragma endregion

#pragma region Action

public:
    UFUNCTION(BlueprintCallable, Category = "Action")
    bool IsFullHeightPartTotem() const;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void SetupTotemDA(UTotemDataAsset* TotemDA);

private:
    UFUNCTION()
    void RegisterBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

    UFUNCTION()
    void RegisterEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

#pragma endregion

#pragma region DataTotem

protected:
    // @protected radius sphere attack
    UPROPERTY(EditAnywhere, Category = "Settings Data Totem", meta = (DisplayName = "Радиус атаки", ClampMin = "10.0"))
    float RadiusSphereAttack{150.0f};

    // @protected Height totem
    UPROPERTY(EditAnywhere, Category = "Settings Data Totem", meta = (DisplayName = "Высота тотема", ClampMin = "1"))
    int32 HeightTotem{1};

    // @protected The distance between the gaps
    UPROPERTY(EditAnywhere, Category = "Settings Data Totem", meta = (DisplayName = "Расстояние между промежутками", ClampMin = "10.0", ForceUnits = "cm"))
    float DistanceGaps{50.0f};

    UPROPERTY(EditAnywhere, Category = "Settings Data Totem", meta = (DisplayName = "Время сброса эффектов", ClampMin = "0.1"))
    float ResetTime{3.0f};

private:
    UPROPERTY()
    TArray<FDataSlotTotem> ArrayDataSlotsTotem;

    UPROPERTY()
    TArray<AActor*> TargetActors;

    TArray<FDataSlotTotem> GenerateSetSlotsTotem() const;
    int32 GetFreeSlotIndexForTotem() const;

#pragma endregion
};
