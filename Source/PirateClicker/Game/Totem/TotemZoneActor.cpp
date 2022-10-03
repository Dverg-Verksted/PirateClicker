// This section is the property of the Dverg Verksted team


#include "Game/Totem/TotemZoneActor.h"
#include "DrawDebugHelpers.h"
#include "PartTotemActor.h"
#include "TotemDataAsset.h"
#include "Components/SphereComponent.h"
#include "Library/PirateClickerLibrary.h"

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
static TAutoConsoleVariable<bool> EnableD_Totem(TEXT("Pirate.ShowDebugTotem"), false, TEXT("Enable the display of debag information on TotemZone from canvas panel"), ECVF_Cheat);
#endif

#pragma region Default

// Sets default values
ATotemZoneActor::ATotemZoneActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root scene component"));
    SetRootComponent(RootScene);

    SphereAttackCollision = CreateDefaultSubobject<USphereComponent>(FName("Sphere attack component"));
    SphereAttackCollision->SetupAttachment(RootScene);
    SphereAttackCollision->SetSphereRadius(RadiusSphereAttack);
}

// Called when the game starts or when spawned
void ATotemZoneActor::BeginPlay()
{
    Super::BeginPlay();

    if (!CHECKED(RootScene != nullptr, "Root scene component is nullptr")) return;
    if (!CHECKED(SphereAttackCollision != nullptr, "Sphere attack component is nullptr")) return;

    ArrayDataSlotsTotem = GenerateSetSlotsTotem();
}

void ATotemZoneActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    ArrayDataSlotsTotem = GenerateSetSlotsTotem();
    ClearDebugTotem();
}

void ATotemZoneActor::DrawDebugTotem()
{
    const UWorld* WorldEditor = UPirateClickerLibrary::GetWorldInEditor();
    if (!WorldEditor) return;
    FlushPersistentDebugLines(WorldEditor);
    DrawDebugSphere(WorldEditor, GetActorLocation(), RadiusSphereAttack, 12, FColor::Cyan, true, 0.0f, 0, 3);
    for (const auto& Data : ArrayDataSlotsTotem)
    {
        DrawDebugSphere(WorldEditor, Data.SlotPosition, 5.0f, 5, FColor::Red, true, 0.0f, 0, 3);
        DrawDebugBox(WorldEditor, Data.SlotPosition, FVector(50.0f), FColor::Red, true, 0.0f, 0, 3);
    }
}

void ATotemZoneActor::ClearDebugTotem()
{
    const UWorld* WorldEditor = UPirateClickerLibrary::GetWorldInEditor();
    if (!WorldEditor) return;
    FlushPersistentDebugLines(WorldEditor);
}

#if WITH_EDITOR

void ATotemZoneActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!PropertyChangedEvent.Property) return;
    const FString PropertyName = PropertyChangedEvent.GetPropertyName().ToString();
    const FString PropertyMemberName = PropertyChangedEvent.MemberProperty->GetName();
    const FString RadiusSphereAttackName = GET_MEMBER_NAME_STRING_CHECKED(ATotemZoneActor, RadiusSphereAttack);
    const FString HeightTotemName = GET_MEMBER_NAME_STRING_CHECKED(ATotemZoneActor, HeightTotem);
    
    if (PropertyName == RadiusSphereAttackName)
    {
        SphereAttackCollision->SetSphereRadius(RadiusSphereAttack);
    }

    if (PropertyName == HeightTotemName)
    {
        ArrayDataSlotsTotem = GenerateSetSlotsTotem();
    }
}

#endif

// Called every frame
void ATotemZoneActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if UE_EDITOR || UE_BUILD_DEVELOPMENT
    if (EnableD_Totem.GetValueOnGameThread())
    {
        DrawDebugSphere(GetWorld(), GetActorLocation(), RadiusSphereAttack, 12, FColor::Cyan, false, 0.0f, 0, 3);
        for (const auto& Data : ArrayDataSlotsTotem)
        {
            DrawDebugSphere(GetWorld(), Data.SlotPosition, 5.0f, 5, FColor::Red, false, 0.0f, 0, 3);
            DrawDebugBox(GetWorld(), Data.SlotPosition, FVector(50.0f), FColor::Red, false, 0.0f, 0, 3);
        }
    }
#endif
}

#pragma endregion

#pragma region Action

void ATotemZoneActor::SetupTotemDA(UTotemDataAsset* TotemDA)
{
    const int32 IndexPart = GetFreeSlotIndexForTotem();
    if (!CHECKED(IndexPart != INDEX_NONE, "index for free slot is none")) return;

    APartTotemActor* NewPart = GetWorld()->SpawnActor<APartTotemActor>(APartTotemActor::StaticClass());
    if (!CHECKED(NewPart != nullptr, "New part for totem is nullptr")) return;

    NewPart->GetMeshPartTotem()->SetStaticMesh(TotemDA->TotemMesh);
    NewPart->SetActorLocation(ArrayDataSlotsTotem[IndexPart].SlotPosition);
    ArrayDataSlotsTotem[IndexPart].TotemActor = NewPart;
    ArrayDataSlotsTotem[IndexPart].TotemDA = TotemDA;
}

void ATotemZoneActor::RegisterBeginOverlap()
{
    
}

void ATotemZoneActor::RegisterEndOverlap()
{
    
}

TArray<FDataSlotTotem> ATotemZoneActor::GenerateSetSlotsTotem() const
{
    TArray<FDataSlotTotem> ArrayDataSlotTotems;
    FVector StartPosition = GetActorLocation();
    for (int32 i = 0; i < HeightTotem; ++i)
    {
        FDataSlotTotem DataSlotTotem;
        DataSlotTotem.SlotPosition = StartPosition;
        StartPosition += FVector(0.0f, 0.0f, DistanceGaps);
        ArrayDataSlotTotems.Add(DataSlotTotem);
    }
    return ArrayDataSlotTotems;
}

int32 ATotemZoneActor::GetFreeSlotIndexForTotem() const
{
    for (int32 i = 0; i < ArrayDataSlotsTotem.Num(); ++i)
    {
        if (ArrayDataSlotsTotem.IsValidIndex(i) && ArrayDataSlotsTotem[i].IsFreeSlot())
            return i;
    }
    return INDEX_NONE;
}

#pragma endregion
