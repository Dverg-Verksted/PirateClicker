// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMeshClass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateLevelMeshLeftSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateLevelMeshRightSignature);

UCLASS(HideCategories=("Replication","Input","Actor","LOD","Cooking","Collision","Rendering","Actor Tick"))
class PIRATECLICKER_API ALevelMeshClass : public AActor
{
    GENERATED_BODY()

#pragma region Default
    
public:
    ALevelMeshClass();

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components and Variables
//Components
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelMesh Settings")
    USceneComponent* SceneRootComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelMesh Settings")
    UStaticMeshComponent* LevelMeshStorage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelMesh Settings")
    USceneCaptureComponent2D* LevelMeshCamera;
//Variables
private:
    UPROPERTY(BlueprintAssignable,BlueprintCallable)
    FRotateLevelMeshLeftSignature RotateLevelMeshLeftNotify;
    UPROPERTY(BlueprintAssignable,BlueprintCallable)
    FRotateLevelMeshLeftSignature RotateLevelMeshRightNotify;

    UPROPERTY()
    FRotator LevelMeshRotationRate{0,5,0};

#pragma endregion

#pragma region Action

public:
    UFUNCTION(BlueprintCallable)
    void RotateLevelMeshLeft();
    UFUNCTION(BlueprintCallable)
    void RotateLevelMeshRight();

#pragma endregion

};