// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldChest.generated.h"

UCLASS(HideCategories = ("Rendering", "Collision", "Input", "Actor", "Cooking", "LOD", "Replication"))
class PIRATECLICKER_API AGoldChest : public AActor
{
    GENERATED_BODY()

#pragma region Default
public:
    // Set Default Values
    AGoldChest();

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:
    // Scene root component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gold Chest Blueprint Settings")
    USceneComponent* SceneRootComponent;

    // Mesh Settings
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gold Chest Blueprint Settings")
    UStaticMeshComponent* MeshStorage;

#pragma endregion
};
