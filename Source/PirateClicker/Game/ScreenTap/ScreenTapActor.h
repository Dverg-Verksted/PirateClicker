// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ScreenTapActor.generated.h"

UCLASS(HideCategories = ("Rendering","Replication","Collision","Actor","LOD","Cooking","Input"))
class PIRATECLICKER_API AScreenTapActor : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
    AScreenTapActor();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float ActorLifeSpanTime{3.0f};

    UPROPERTY(EditDefaultsOnly)
    USceneComponent* SceneRootComponent;
    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* MeshStorage;
    UPROPERTY()
    UWidgetComponent* WidgetComponent;

};
