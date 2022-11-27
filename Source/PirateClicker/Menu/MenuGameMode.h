// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"



UENUM()
enum class EStateMenuMode:uint8
{
    None,
    MainMenu,
    SettingsMenu,
    ShopMenu,
    LoadMenu,
    LevelSelectMenu,
};

#pragma region Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeMenuStateNotifySignature,EStateMenuMode ,NewState);

#pragma endregion

UCLASS()
class PIRATECLICKER_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Actions
public:
    
    void MenuStateChange(EStateMenuMode);
    UFUNCTION(BlueprintCallable)
    EStateMenuMode GetCurrentMenuState();
    
    FChangeMenuStateNotifySignature OnChangeMenuStateNotify;

    virtual void  StartPlay() override;
    
private:
    EStateMenuMode StateMenuMode{EStateMenuMode::None};

#pragma endregion 
	
};
