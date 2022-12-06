// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoreDiaryMasterWidget.generated.h"

UENUM()
enum class EDiaryState:uint8
{
    None,
    Reading,
    ChangePage
};

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangePageLeftSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangePageRightSignature);

#pragma endregion

UCLASS()
class PIRATECLICKER_API ULoreDiaryMasterWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Action

protected:
    virtual void NativeConstruct() override;
    
public:   
    UFUNCTION()
    void ChangePageLeftEvent();
    UFUNCTION()
    void ChangePageRightEvent();

    UFUNCTION(BlueprintCallable)
    EDiaryState GetCurrentDiaryState();

    UFUNCTION()
    void SetMaxPageAmount(int32 NewMaxPageAmount);

#pragma endregion

#pragma region Components
    
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* ChangePageLeftAnimation;
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* ChangePageRightAnimation;

#pragma endregion

#pragma region Variables
    
    FChangePageLeftSignature ChangePageLeftNotify;
    FChangePageRightSignature ChangePageRightNotify;
    
private:
    EDiaryState CurrentDiaryState {EDiaryState::None};

    UPROPERTY()
    int32 MinPageAmount{1};
    UPROPERTY()
    int32 MaxPageAmount{0};
    UPROPERTY()
    int32 CurrentPageNumber{0};

#pragma endregion
    
	
};
