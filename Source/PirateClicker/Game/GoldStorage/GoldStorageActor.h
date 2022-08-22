// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldStorageActor.generated.h"

UCLASS()
class PIRATECLICKER_API AGoldStorageActor : public AActor
{
	GENERATED_BODY()

#pragma region Default
    
public:	
	AGoldStorageActor();

    UFUNCTION(BlueprintCallable,Category = "Gold settings")
    int32 GetCurrentGold();
    UFUNCTION(BlueprintCallable,Category = "Gold settings")
    void SetCurrentGold(float GoldToSet);

    void SetStorageStaticMesh();

    void PirateMovingDirectionChange();

private:
    UPROPERTY(EditInstanceOnly,Category = "Storage Settings",meta = (ClampMin = "0",ToolTip = "Показывает текущее золото в хранилище"))
    int32 CurrentGold = 0;

protected:
    virtual void BeginPlay() override;

    UPROPERTY (EditInstanceOnly,Category = "Storage Settings",meta = (ToolTip = "Тут назначаем меш для хранилища"))
    UStaticMeshComponent *StaticMeshToChange;

    UStaticMesh* StorageStaticMesh;

    UPROPERTY (EditInstanceOnly, Category = "Storage Settings",meta = (ToolTip = "Тут назначаем зону, где пират после сбора сундука будет идти на корабль"))
    class UCapsuleComponent *TriggerCapsule ;

#pragma endregion

#pragma region Components

protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshStorage;

#pragma endregion
};
