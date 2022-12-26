// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MenuGameMode.h"
#include "MenuMasterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATECLICKER_API UMenuMasterWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Variables
protected:
    UPROPERTY()
    AMenuGameMode* MenuGameMode;

#pragma endregion

#pragma region Action

protected:

    UFUNCTION()
    virtual void NativeConstruct() override;

#pragma endregion
};
