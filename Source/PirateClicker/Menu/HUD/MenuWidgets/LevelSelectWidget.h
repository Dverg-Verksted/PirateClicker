// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Menu/HUD/MenuMasterWidget.h"
#include "WidgetsComponents/LevelMesh/LevelMeshClass.h"
#include "LevelSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATECLICKER_API ULevelSelectWidget : public UMenuMasterWidget
{
	GENERATED_BODY()

#pragma region WidgetComponents

public:
    
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* LevelSwitchLeftArrow;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* LevelSwitchRightArrow;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(Transient,meta = (BindWidget))
    UOverlay* LevelMeshOverlay;
    UPROPERTY(Transient,meta = (BindWidget))
    UImage* LevelMeshRenderTexture;
    UPROPERTY(Transient,meta = (BindWidget))
    UButton* LevelMeshButton;
    
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* ArrowButtonsAnimation;
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* BackButtonAnimation;

#pragma endregion

#pragma region Variables

protected:
    UPROPERTY(BlueprintReadOnly)
    bool isFirstLvlSelected{false};
    UPROPERTY(BlueprintReadOnly)
    bool isLastLvlSelected{false};
    UPROPERTY()
    FVector2D LastTapLocation;
    UPROPERTY(EditAnywhere)
    TSubclassOf<ALevelMeshClass> LevelMeshSubClass;

private:
    UPROPERTY()
    TArray<FName> LevelsArray;
    UPROPERTY()
    int32 LevelNumber;
    UPROPERTY()
    ALevelMeshClass* RenderingLevelMesh;

#pragma endregion

#pragma region Actions

public:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void MoveLvlAtScreenLeft();
    UFUNCTION()
    void MoveLevelAtScreenRight();
    UFUNCTION()
    void BackToStartMenuWidget();
    UFUNCTION()
    void RotateLevelMeshByTap();

#pragma endregion
	
};
