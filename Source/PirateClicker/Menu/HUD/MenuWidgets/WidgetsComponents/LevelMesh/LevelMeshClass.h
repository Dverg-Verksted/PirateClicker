// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMeshClass.generated.h"

UCLASS(HideCategories=("Replication","Input","Actor","LOD","Cooking","Collision","Rendering"))
class PIRATECLICKER_API ALevelMeshClass : public AActor
{
    GENERATED_BODY()

#pragma region Default
    
public:
    ALevelMeshClass();

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:
    // Scene root component
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelMesh Settings")
    USceneComponent* SceneRootComponent;

    // Mesh Settings
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelMesh Settings")
    UStaticMeshComponent* MeshStorage;

#pragma endregion

};