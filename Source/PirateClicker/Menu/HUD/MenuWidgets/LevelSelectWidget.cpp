// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuWidgets/LevelSelectWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Net/Core/Connection/NetResult.h"
#include "WidgetsComponents/LevelMesh/LevelMeshClass.h"

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LevelSwitchLeftArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLvlAtScreenLeft);
    LevelSwitchRightArrow->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::MoveLevelAtScreenRight);
    BackButton->OnClicked.AddDynamic(this,&ThisClass::ULevelSelectWidget::BackToStartMenuWidget);
}
void ULevelSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    RotateLevelMeshByTap();
}

void ULevelSelectWidget::MoveLevelAtScreenRight()
{
    if (isLastLvlSelected)return;

    PlayAnimation(ArrowButtonsAnimation);
    LevelNumber++;
}
void ULevelSelectWidget::MoveLvlAtScreenLeft()
{
    if (isFirstLvlSelected)return;

    PlayAnimation(ArrowButtonsAnimation);
    LevelNumber--;
}

void ULevelSelectWidget::BackToStartMenuWidget()
{
    PlayAnimation(BackButtonAnimation);
    MenuGameMode->MenuStateChange(EStateMenuMode::MainMenu);
}

void ULevelSelectWidget::RotateLevelMeshByTap()
{
    if (LevelMeshButton->IsPressed())
    {
        float TapLocationX,TapLocationY;
        GetWorld()->GetFirstPlayerController()->GetMousePosition(TapLocationX,TapLocationY);
        LastTapLocation.X = TapLocationX;
        LastTapLocation.Y = TapLocationY;
        LastTapLocation.Normalize(0.4f);
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("%f = X location,%f= Y location"),LastTapLocation.X,LastTapLocation.Y));
        RenderingLevelMesh = Cast<ALevelMeshClass>(UGameplayStatics::GetActorOfClass(GetWorld(),LevelMeshSubClass));
        if (LastTapLocation.Y <= 0.42f)
        {
            RenderingLevelMesh->RotateLevelMeshLeft();
        }
        if (LastTapLocation.Y >= 0.43f)
        {
            RenderingLevelMesh->RotateLevelMeshRight();
        }
    }
}
