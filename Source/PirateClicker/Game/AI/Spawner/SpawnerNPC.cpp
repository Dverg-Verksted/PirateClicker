// This section is the property of the Dverg Verksted team

#include "Game/AI/Spawner/SpawnerNPC.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_SpawnerNPC(TEXT("Pirate.ShowDebugSpawnerNPC"), false, TEXT("Enable the display of debag information on SpawnerNPC from canvas panel"), ECVF_Cheat);
#endif

#pragma region Default

// Sets default values
ASpawnerNPC::ASpawnerNPC()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    Billboard = CreateDefaultSubobject<UBillboardComponent>(FName("Billboard"));
    Billboard->SetupAttachment(RootScene);

    SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Sphere collision"));
    SphereCollision->SetupAttachment(RootScene);
}

void ASpawnerNPC::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_SpawnerNPC.GetValueOnGameThread())
    {
        UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Name: [%s]"), *GetName()),
            true, false, FLinearColor::Blue, 0.0f);
    }
#endif
}

// Called when the game starts or when spawned
void ASpawnerNPC::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(Billboard != nullptr, "Billboard is nullptr")) return;
    if (!CHECKED(SphereCollision != nullptr, "Sphere Collision is nullptr")) return;
    
}

#pragma endregion
