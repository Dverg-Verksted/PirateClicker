// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ScreenTapActor.generated.h"

UCLASS(HideCategories = ("Rendering", "Replication", "Collision", "Actor", "LOD", "Cooking", "Input", "Actor Tick"))
class PIRATECLICKER_API AScreenTapActor : public AActor
{
    GENERATED_BODY()

#pragma region Default
protected:
    virtual void BeginPlay() override;

public:
    AScreenTapActor();

#pragma endregion

#pragma region Settings

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0"))
    float ActorLifeSpanTime{3.0f};

#pragma endregion

#pragma region Components

    UPROPERTY()
    USceneComponent* SceneRootComponent;
    UPROPERTY()
    UStaticMeshComponent* MeshStorage;

    UPROPERTY()
    UWidgetComponent* WidgetComponent;

#pragma endregion
};
