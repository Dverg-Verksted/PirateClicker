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

    UFUNCTION(BlueprintCallable,Category = "Gold settings")
    int32 GetCurrentGold();
    UFUNCTION(BlueprintCallable,Category = "Gold settings")
    void SetCurrentGold(float GoldToSet);

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
    UPROPERTY(EditInstanceOnly,Category = "Storage Settings",meta = (ClampMin = "0",ToolTip = "Показывает текущее золото в хранилище"))
    int32 CurrentGold = 0;

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:

    UPROPERTY (EditInstanceOnly,Category = "Storage Settings",meta = (ToolTip = "Тут назначаем меш для хранилища"))
    UStaticMesh *StaticMeshToChange;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshStorage;

    UPROPERTY(EditInstanceOnly,Category = "Storage Settings", meta = (ToolTip = "Sphere Collision"))
    ETypeCollision TypeCollision;


#pragma endregion
};
