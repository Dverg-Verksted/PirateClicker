// This section is the property of the Dverg Verksted team

#include "Game/Totem/PartTotemActor.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

// Sets default values
APartTotemActor::APartTotemActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    MeshPartTotem = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh part totem component"));
    MeshPartTotem->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void APartTotemActor::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(MeshPartTotem != nullptr, "Mesh part totem is nullptr")) return;
}

#pragma endregion
