// This section is the property of the Dverg Verksted team

#include "Game/Player/GamePC.h"

#include "DrawDebugHelpers.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_GamePC(TEXT("Pirate.ShowDebugGamePC"), false, TEXT("Enable debug information for game player contorller"), ECVF_Cheat);
#endif

#pragma region Default

AGamePC::AGamePC()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;
}

void AGamePC::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true;
}

void AGamePC::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!CHECKED(InputComponent != nullptr, "Input component is nullptr")) return;

    InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ThisClass::RegisterTouchPressed);
}

void AGamePC::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_GamePC.GetValueOnGameThread())
    {
        DrawDebugSphere(GetWorld(), TouchLocation, 12.0f, 12, FColor::Red, false, 0.0f, 0, 2.0f);
    }
#endif
}

void AGamePC::RegisterTouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
    FHitResult HitResult;
    GetHitResultUnderFinger(FingerIndex, ECollisionChannel::ECC_Visibility, false, HitResult);
    if (HitResult.bBlockingHit && HitResult.GetActor())
    {
        LOG_PIRATE(ELogVerb::Display,
            FString::Printf(TEXT("Pressed touch index: [%s] | Location: [%s] | Actor: [%s]"), *UEnum::GetValueAsString(FingerIndex), *HitResult.Location.ToString(), *HitResult.GetActor()->GetName()));
        TouchLocation = HitResult.Location;
        OnHitActor.Broadcast(HitResult.GetActor());
    }
}

#pragma endregion
