// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GoldStorageActor.generated.h"

class AGoldChest;
class APirateActorBase;
UENUM()
enum class ETypeCollision : uint8
{
    Box UMETA(DisplayName = "Боксовая коллизия"),
    Sphere UMETA(DisplayName = "Сферовая коллизия")
};

UCLASS(HideCategories = ("Input", "Replication", "Actor", "LOD", "Cooking", "Rendering", "Collision"))
class PIRATECLICKER_API AGoldStorageActor : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    AGoldStorageActor();

    UFUNCTION(BlueprintCallable, Category = "Gold settings", meta = (ToolTip = "Функция отдает текущее кол-во сундуков"))
    int32 GetCurrentGold();
    UFUNCTION(BlueprintCallable, Category = "Gold settings", meta = (ToolTip = "Функция назначает текущее кол-во сундуков"))
    void SetCurrentGold(int32 GoldToSet);
    UFUNCTION(BlueprintCallable, Category = "Gold settings", meta = (ToolTip = "Функция назначает текущее кол-во сундуков"))
    void UpperCountGold();

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
    UPROPERTY(EditInstanceOnly, Category = "Storage component settings", meta = (ClampMin = "0", ToolTip = "Показывает текущее золото в хранилище"))
    int32 CurrentGold = 0;

    int32 MaxGold = 0;

    bool isBoxCollision;

protected:
    virtual void BeginPlay() override;

#pragma endregion
#pragma region Components

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    UPROPERTY(EditInstanceOnly, Category = "Storage component settings", meta = (ToolTip = "Тут назначаем меш для хранилища"))
    UStaticMesh* MeshToChange;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshStorage;

    UPROPERTY(EditInstanceOnly, Category = "Storage component settings", meta = (ToolTip = "Тут назначаем коллизию, которая будет отправилять пирата обратно"))
    ETypeCollision TypeCollision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage component settings")
    UBoxComponent* BoxCollision;
    UPROPERTY(EditInstanceOnly, Category = "Storage component settings",
        meta = (ClampMin = "1", EditCondition = "TypeCollision == ETypeCollision::Box", EditConditionHides, ToolTip = "Тут назначаем размер боксовой коллизии"));
    float BoxCollisionSize{100.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Storage component settings")
    USphereComponent* SphereCollision;
    UPROPERTY(EditInstanceOnly, Category = "Storage component settings",
        meta = (Clampmin = "1", EditCondition = "TypeCollision == ETypeCollision::Sphere", EditConditionHides, ToolTip = "Тут назначаем радиус сферовой коллизии"));
    float SphereCollisionRadius{100.0f};

    UPROPERTY(EditInstanceOnly, Category = "Storage component settings", meta = (ToolTip = "Тут назначаем сундук, который будет выдаваться пирату при оверлепе"))
    TSubclassOf<AGoldChest> GoldChestToGive;

#pragma endregion
#pragma region Delegate
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGoldStorageChestTaken, class APirateActorBase*, TakenChestPirate, AGoldStorageActor*, GoldChestFromStorage);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGoldStorageEmptySignature);

protected:
    UPROPERTY(BlueprintCallable, Category = "Gold storage", meta = (ToolTip = "Делегат, который вызывается, когда хранилище пустое"))
    FGoldStorageEmptySignature GoldStorageEmpty;
    UPROPERTY(BlueprintCallable, Category = "Gold storage", meta = (ToolTip = "Делегат, который вызывается, когда пираты оверлапят хранилище"))
    FGoldStorageChestTaken GoldStorageChestTaken;

#pragma endregion
#pragma region Action
    UFUNCTION(BlueprintImplementableEvent)
    void OnChangeGoldCount();

private:
    UFUNCTION()
    void RegisterActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
    UFUNCTION()
    void RegisterActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
    void CollisionChecker();

    UPROPERTY()
    TArray<APirateActorBase*> ArrayTargetPirate;

#pragma endregion
};
