// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "MenuMasterWidget.h"
#include "GameFramework/HUD.h"
#include "Menu/MenuGameMode.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PIRATECLICKER_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UMenuMasterWidget> StartWidget;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UMenuMasterWidget> SettingsWidget;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UMenuMasterWidget> ShopWidget;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UMenuMasterWidget> LevelSelectWidget;

    virtual void BeginPlay() override;
    
    UFUNCTION()
    void RegisterChangeMenuState(EStateMenuMode NewMenuState);

    UPROPERTY()
    TMap<EStateMenuMode,UMenuMasterWidget*> SetStateMenuWidgets;

    UPROPERTY()
    UMenuMasterWidget* CurrentVisibleWidget{nullptr};
    
};
