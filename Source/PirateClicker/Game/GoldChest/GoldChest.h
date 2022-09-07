// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldChest.generated.h"

//Chest States
UENUM()
enum class EGoldChestState:uint8
{
    Taken UMETA (DisplayName = "Взят в руки"),
    Dropped UMETA (DisplayName = "Лежит на земле")
};

UCLASS(HideCategories = ("Rendering","Collision","Input","Actor","Cooking","LOD","Replication"))
class PIRATECLICKER_API AGoldChest : public AActor
{
	GENERATED_BODY()

#pragma region Default
public:
//Set Default Values
	AGoldChest();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

public:
    UFUNCTION(BlueprintCallable,Category = "Chest State",meta = (ToolTip = "Функция для получения текущего состояния сундука"))
    EGoldChestState GetGoldChestState();
    
protected:
//Scene root component
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Gold Chest Blueprint Settings")
    USceneComponent* SceneRootComponent;

//Mesh Settings
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Gold Chest Blueprint Settings")
    UStaticMeshComponent* MeshStorage;
    UPROPERTY(EditInstanceOnly,Category = "Gold Chest settings",meta = (ToolTip= "Тут назначается меш для сундука"))
    UStaticMesh* MeshToChange;
    
private:
//Chest State Variable
    UPROPERTY(EditInstanceOnly,Category = "Gold Chest settings")
    EGoldChestState ChestState ;

#pragma endregion 
   

};
