// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GoldStorageActor.generated.h"


UENUM()
enum class ETypeCollision:uint8
{
    Box UMETA(DisplayName = "Боксовая коллизия"),
    Sphere UMETA(DisplayName = "Сферовая коллизия")
};

UCLASS(HideCategories = ("Input","Replication","Actor","LOD","Cooking","Rendering","Collision"))
class PIRATECLICKER_API AGoldStorageActor : public AActor
{
	GENERATED_BODY()

#pragma region Default
    
public:	
	AGoldStorageActor();

    UFUNCTION(BlueprintCallable,Category = "Gold settings",meta = (ToolTip = "Функция отдает текущее кол-во сундуков"))
    int32 GetCurrentGold();
    UFUNCTION(BlueprintCallable,Category = "Gold settings",meta = (ToolTip = "Функция назначает текущее кол-во сундуков"))
    void SetCurrentGold(float GoldToSet);

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
    UPROPERTY(EditInstanceOnly,Category = "Storage component settings",meta = (ClampMin = "0",ToolTip = "Показывает текущее золото в хранилище"))
    int32 CurrentGold = 0;

protected:
    virtual void BeginPlay() override;

#pragma endregion
#pragma region Components

protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;
    
    UPROPERTY (EditInstanceOnly,Category = "Storage component settings",meta = (ToolTip = "Тут назначаем меш для хранилища"))
    UStaticMesh *MeshToChange;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshStorage;

    
    UPROPERTY(EditInstanceOnly,Category = "Storage component settings", meta = (ToolTip = "Тут назначаем коллизию, которая будет отправилять пирата обратно"))
    ETypeCollision TypeCollision;

    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Storage component settings")
    UBoxComponent* BoxCollision;
    UPROPERTY(EditInstanceOnly,Category = "Storage component settings",meta = (ClampMin = "1", EditCondition = "TypeCollision == ETypeCollision::Box",EditConditionHides,
        ToolTip = "Тут назначаем размер боксовой коллизии"));
    float BoxCollisionSize {100.f}; 

    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Storage component settings")
    USphereComponent* SphereCollision;
    UPROPERTY(EditInstanceOnly,Category = "Storage component settings",meta = (Clampmin = "1",EditCondition = "TypeCollision == ETypeCollision::Sphere",EditConditionHides,
        ToolTip = "Тут назначаем радиус сферовой коллизии"));
    float SphereCollisionRadius {100.0f}; 

#pragma endregion
#pragma region Action

private:
    void RegisterActorBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    void CollisionChecker();

#pragma endregion
};
