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
	// Sets default values for this actor's properties
	AGoldStorageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshStorage;

#pragma endregion
};
