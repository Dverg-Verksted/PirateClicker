// This section is the property of the Dverg Verksted team

#include "Game/Player/GamePC.h"
#include "DrawDebugHelpers.h"
#include "Game/AI/Pirates/PirateActorBase.h"
#include "Game/GameMode/StoryGMBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/ScreenTap/ScreenTapActor.h"
#include "Kismet/GameplayStatics.h"
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

    StoryGM = Cast<AStoryGMBase>(GetWorld()->GetAuthGameMode());
    if (!CHECKED(StoryGM != nullptr, "Story gm is nullptr")) return;
    StoryGM->OnChangeStateGame.AddDynamic(this, &ThisClass::RegisterChangeStateGame);
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
        DrawDebugSphere(GetWorld(), TouchLocation, 100.0f, 12, FColor::Red, false, 0.0f, 0, 2.0f);
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
        const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{};
        const TArray<AActor*> ActorsToIgnore{GetPawn()};
        TArray<AActor*> OutActors;
        UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitResult.Location, 100.0f, ObjectTypes, AActor::StaticClass(), ActorsToIgnore, OutActors);
        SpawnActorWithTap(HitResult.Location);

        OnPushArrayHit.Broadcast(OutActors);
        for (AActor* Actor : OutActors)
        {
            OnHitActor.Broadcast(Actor);
            if (Actor->IsA(APirateActorBase::StaticClass()))
            {
                UGameplayStatics::ApplyDamage(Actor, 5.0f, this, GetPawn(), UDamageType::StaticClass());
            }
        }
    }
}

void AGamePC::RegisterChangeStateGame(const EStateGame& NewState)
{
    switch (NewState)
    {
        case EStateGame::InProgress:
        {
            SetInputMode(FInputModeGameAndUI());
            bShowMouseCursor = true;
            SetPause(false);
            break;
        }
        case EStateGame::GameLose:
        {
            SetInputMode(FInputModeUIOnly());
            bShowMouseCursor = true;
            SetPause(true);
            break;
        }
        case EStateGame::GameWin:
        {
            SetInputMode(FInputModeUIOnly());
            bShowMouseCursor = true;
            SetPause(true);
            break;
        }
    }
}
void AGamePC::SpawnActorWithTap(FVector TapLocation)
{
    if (ScreenTapClass)
    {
        ScreenTapClass->GetClass()->MarkPendingKill();
        ScreenTapClass->Destroy();
    }
    FTransform TapActorSpawnTransform;
    TapActorSpawnTransform.SetLocation(TapLocation);

    UClass* SubClassTapScreen = PathToScreenTap.TryLoadClass<AScreenTapActor>();
    if (!SubClassTapScreen) return;

    ScreenTapClass = GetWorld()->SpawnActorDeferred<AScreenTapActor>(SubClassTapScreen, TapActorSpawnTransform);
    ScreenTapClass->FinishSpawning(TapActorSpawnTransform);
}

#pragma endregion
