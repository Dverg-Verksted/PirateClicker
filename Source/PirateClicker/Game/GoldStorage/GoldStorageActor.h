// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldStorageActor.generated.h"


UENUM()
enum class ETypeCollision:uint8
{
    Box,
    Sphere
};

UCLASS(HideCategories = ("Input","Replication","Actor","LOD","Cooking","Rendering"))
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

    void OnActorBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    

    void CollisionChecker();

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
    UPROPERTY(EditInstanceOnly,Category = "Storage Settings",meta = (ClampMin = "0",ToolTip = "Показывает текущее золото в хранилище"))
    int32 CurrentGold = 0;

    UPROPERTY(EditInstanceOnly,Category = "Storage component settings",meta = (ToolTip = "Тут назначаем радиус сферовой коллизии"));
    float SphereCollisionRadius; 
    UPROPERTY(EditInstanceOnly,Category = "Storage component settings",meta = (ToolTip = "Тут назначаем размер боксовой коллизии"));
    float BoxCollisionSize; 


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


#pragma endregion
};
