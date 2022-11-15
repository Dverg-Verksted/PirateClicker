// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Menu/HUD/MenuMasterWidget.h"
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

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* ArrowButtonsAnimation;
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* BackButtonsAnimation;

#pragma endregion

#pragma region Variables

protected:
    UPROPERTY(BlueprintReadOnly)
    bool isFirstLvlSelected{false};
    UPROPERTY(BlueprintReadOnly)
    bool isLastLvlSelected{false};

#pragma endregion

#pragma region Actions

public:
    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void MoveLvlAtScreenLeft();
    UFUNCTION()
    void MoveLevelAtScreenRight();
    UFUNCTION()
    void BackToStartMenuWidget();

#pragma endregion

#pragma region Variables

private:

    UPROPERTY()
    TArray<FName> LevelsArray;
    UPROPERTY()
    int32 LevelNumber;

#pragma endregion 
	
};
