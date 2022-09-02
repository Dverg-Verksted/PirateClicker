// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Game/GameMode/StoryGMBase.h"
#include "Game/HUD/DebugHUD.h"
#include "GameHUD.generated.h"

class UGameUserWidgetBase;
/**
 * @class Base game play HUD
 */
UCLASS()
class PIRATECLICKER_API AGameHUD : public ADebugHUD
{
    GENERATED_BODY()

public:
    AGameHUD();

protected:
    // Draw the HUD.
    virtual void DrawHUD() override;

    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

#pragma region DataHUD

public:
    /**
     * @public Get Game Widgets
     * @return TMap<EStateGame, UGameUserWidgetBase*>
     **/
    UFUNCTION(BlueprintCallable, Category = "AGameHUD | GetDataHUD")
    TMap<EStateGame, UGameUserWidgetBase*> GetGameWidgets() const { return GameWidgets; }

protected:
    // @protected Game progress widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Виджет игрового процесса"))
    TSubclassOf<UGameUserWidgetBase> ProgressWidget;

    // @protected Current pointer to StoryGM
    UPROPERTY()
    AStoryGMBase* StoryGM;

    // @protected Current Active widget
    UPROPERTY()
    UGameUserWidgetBase* ActiveWidget{nullptr};

    // @protected Set game widgets
    UPROPERTY()
    TMap<EStateGame, UGameUserWidgetBase*> GameWidgets;

#pragma endregion

#pragma region Action

private:
    UFUNCTION()
    void RegisterChangedStateGame(const EStateGame& NewState);

#pragma endregion
};
