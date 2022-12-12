// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LoreDiaryMasterWidget.generated.h"

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

#pragma endregion

#pragma region Components

    UPROPERTY(Transient,meta = (BindWidget))
    UButton* BackButton;
    
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* ChangePageLeftAnimation;
    UPROPERTY(Transient,meta = (BindWidgetAnim))
    UWidgetAnimation* ChangePageRightAnimation;

#pragma endregion

#pragma region Variables
    
    FChangePageLeftSignature ChangePageLeftNotify;
    FChangePageRightSignature ChangePageRightNotify;
    
private:
    bool CanChangePage{false};

#pragma endregion
    
	
};
