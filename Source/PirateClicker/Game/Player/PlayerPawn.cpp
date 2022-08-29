// This section is the property of the Dverg Verksted team

#include "Game/Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

// Sets default values
APlayerPawn::APlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Sphere collision"));
    SphereCollision->SetupAttachment(RootScene);
    SphereCollision->SetCollisionProfileName(FName("OverlapAll"));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring arm component"));
    SpringArm->SetupAttachment(RootScene);
    SpringArm->bEnableCameraLag = true;
    SpringArm->TargetArmLength = CameraDistance;

    Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera component"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene is nullptr")) return;
    if (!CHECKED(SphereCollision != nullptr, "Sphere Collision is nullptr")) return;
    if (!CHECKED(SpringArm != nullptr, "Spring Arm is nullptr")) return;
    if (!CHECKED(Camera != nullptr, "Camera is nullptr")) return;
}

#if WITH_EDITOR

void APlayerPawn::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
    Super::PostEditChangeChainProperty(PropertyChangedEvent);

    if (!CHECKED(PropertyChangedEvent.Property != nullptr, "Property is nullptr")) return;

    if (PropertyChangedEvent.Property->GetName() == TEXT("CameraDistance"))
    {
        SpringArm->TargetArmLength = CameraDistance;
    }

    if (PropertyChangedEvent.PropertyChain.GetActiveMemberNode()->GetValue()->GetName() == TEXT("RotatePawn"))
    {
        SpringArm->SetRelativeRotation(RotatePawn);
    }
}

#endif

#pragma endregion