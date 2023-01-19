// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Delegates/DelegateCombinations.h"
#include "LoreDiaryPageButtonComponent.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenDiaryPageSignature,class ULoreDiaryPageButtonComponent*,PageButton);

#pragma endregion

UCLASS()
class PIRATECLICKER_API ULoreDiaryPageButtonComponent : public UUserWidget
{
	GENERATED_BODY()

#pragma region Components

public:
    UPROPERTY(Transient,EditInstanceOnly,meta = (BindWidget))
    UButton* DiaryPageButton;
    UPROPERTY(Transient,EditInstanceOnly,meta = (BindWidget))
    UTextBlock* DiaryPageTextBlock;

#pragma endregion

#pragma region Variables

public:
    UPROPERTY(EditInstanceOnly,BlueprintReadOnly)
    FText DiaryPageButtonName;
    UPROPERTY(EditInstanceOnly,BlueprintReadOnly)
    FText DiaryPageButtonLoreText;
    
    UPROPERTY(BlueprintAssignable)
    FOnOpenDiaryPageSignature OnOpenDiaryPageNotify;

#pragma endregion

#pragma region Action

protected:
    virtual void NativeConstruct() override;

public:
    UFUNCTION()
    void OpenDiaryPageEvent();

#pragma endregion
	
};
