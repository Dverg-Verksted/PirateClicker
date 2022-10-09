// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PartTotemActor.generated.h"

UCLASS(NotBlueprintable, NotBlueprintType)
class PIRATECLICKER_API APartTotemActor : public AActor
{
    GENERATED_BODY()

#pragma region Default

public:
    // Sets default values for this actor's properties
    APartTotemActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

public:
    /**
     * @public Get root scene component
     * @return USceneComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "Components")
    FORCEINLINE USceneComponent* GetRootScene() const { return RootScene; }

    /**
     * @public Get mesh part totem
     * @return UStaticMeshComponent
     **/
    UFUNCTION(BlueprintCallable, Category = "Components")
    FORCEINLINE UStaticMeshComponent* GetMeshPartTotem() const { return MeshPartTotem; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* RootScene;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UStaticMeshComponent* MeshPartTotem;

#pragma endregion
};
