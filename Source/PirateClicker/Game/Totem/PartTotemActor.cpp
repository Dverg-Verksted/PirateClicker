// This section is the property of the Dverg Verksted team

#include "Game/Totem/PartTotemActor.h"
#include "Library/PirateClickerLibrary.h"

#pragma region Default

// Sets default values
APartTotemActor::APartTotemActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

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
    StartAnimRotateCurve = LoadObject<UCurveFloat>(this, TEXT("CurveFloat'/Game/PirateClicker/Core/Totem/CurveFloat_StartAnimRotate.CurveFloat_StartAnimRotate'"));
    StartAnimScaledCurve = LoadObject<UCurveFloat>(this, TEXT("CurveFloat'/Game/PirateClicker/Core/Totem/CurveFloat_StartAnimScaled.CurveFloat_StartAnimScaled'"));
    NormalAnimRotateCurve = LoadObject<UCurveFloat>(this, TEXT("CurveFloat'/Game/PirateClicker/Core/Totem/CurveFloat_NormalAnimRotate.CurveFloat_NormalAnimRotate'"));
    NormalAnimPosCurve = LoadObject<UCurveFloat>(this, TEXT("CurveFloat'/Game/PirateClicker/Core/Totem/CurveFloat_NormalAnimPos.CurveFloat_NormalAnimPos'"));
    if (!CHECKED(StartAnimRotateCurve != nullptr, "StartAnimRotateCurve is nullptr")) return;
    if (!CHECKED(StartAnimScaledCurve != nullptr, "StartAnimScaledCurve is nullptr")) return;
    if (!CHECKED(NormalAnimRotateCurve != nullptr, "NormalAnimRotateCurve is nullptr")) return;
    if (!CHECKED(NormalAnimPosCurve != nullptr, "NormalAnimPosCurve is nullptr")) return;

    DefaultActorPosition = GetActorLocation();

    FOnTimelineFloat OnStartAnimScaledTimelineFloat;
    OnStartAnimScaledTimelineFloat.BindDynamic(this, &ThisClass::UpdateAnimScaled);

    StartAnimScaledTimeLine.AddInterpFloat(StartAnimScaledCurve, OnStartAnimScaledTimelineFloat);
    StartAnimScaledTimeLine.SetLooping(false);
    StartAnimScaledTimeLine.Play();

    FOnTimelineFloat OnStartAnimRotateTimelineFloat;
    OnStartAnimRotateTimelineFloat.BindDynamic(this, &ThisClass::UpdateAnimRotate);

    FOnTimelineEvent OnFinishStartRotateScaledTimelineEvent;
    OnFinishStartRotateScaledTimelineEvent.BindDynamic(this, &ThisClass::FinishAnimRotate);

    StartAnimRotateTimeLine.AddInterpFloat(StartAnimScaledCurve, OnStartAnimRotateTimelineFloat);
    StartAnimRotateTimeLine.SetTimelineFinishedFunc(OnFinishStartRotateScaledTimelineEvent);
    StartAnimRotateTimeLine.SetLooping(false);
    StartAnimRotateTimeLine.Play();
}

void APartTotemActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    StartAnimRotateTimeLine.TickTimeline(DeltaSeconds);
    StartAnimScaledTimeLine.TickTimeline(DeltaSeconds);
    NormalAnimRotateTimeLine.TickTimeline(DeltaSeconds);
    NormalAnimPosTimeLine.TickTimeline(DeltaSeconds);
}

#pragma endregion

void APartTotemActor::UpdateAnimScaled(float Value)
{
    SetActorScale3D(FVector(Value));
}

void APartTotemActor::UpdateAnimRotate(float Value)
{
    AddActorWorldRotation(FRotator(0.0f, Value, 0.0f));
}

void APartTotemActor::UpdateAnimPos(float Value)
{
    SetActorLocation(FVector(DefaultActorPosition.X, DefaultActorPosition.Y, DefaultActorPosition.Z + Value));
}

void APartTotemActor::FinishAnimRotate()
{
    FOnTimelineFloat OnNormalAnimRotateTimelineFloat;
    OnNormalAnimRotateTimelineFloat.BindDynamic(this, &ThisClass::UpdateAnimRotate);

    NormalAnimRotateTimeLine.AddInterpFloat(NormalAnimRotateCurve, OnNormalAnimRotateTimelineFloat);
    NormalAnimRotateTimeLine.SetLooping(true);
    NormalAnimRotateTimeLine.Play();

    FOnTimelineFloat OnNormalAnimPosTimeLineFloat;
    OnNormalAnimPosTimeLineFloat.BindDynamic(this, &ThisClass::UpdateAnimPos);

    NormalAnimPosTimeLine.AddInterpFloat(NormalAnimPosCurve, OnNormalAnimPosTimeLineFloat);
    NormalAnimPosTimeLine.SetLooping(true);
    NormalAnimPosTimeLine.Play();
}
