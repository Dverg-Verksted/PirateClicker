// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Game/GameMode/StoryGMDataTypes.h"
#include "GameFramework/PlayerController.h"
#include "GamePC.generated.h"

class AScreenTapActor;
class AStoryGMBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitActorSignature, AActor*, HitActor);

/**
 * @class Game player controller
 */
UCLASS()
class PIRATECLICKER_API AGamePC : public APlayerController
{
    GENERATED_BODY()

#pragma region Default

public:
    AGamePC();

protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

    /** Allows the PlayerController to set up custom input bindings. */
    virtual void SetupInputComponent() override;

    /**
     *	Function called every frame on this Actor. Override this function to implement custom logic to be executed every frame.
     *	Note that Tick is disabled by default, and you will need to check PrimaryActorTick.bCanEverTick is set to true to enable it.
     *
     *	@param	DeltaSeconds	Game time elapsed during last frame modified by the time dilation
     */
    virtual void Tick(float DeltaSeconds) override;

private:
    UFUNCTION()
    void RegisterTouchPressed(ETouchIndex::Type FingerIndex, FVector Location);

    UFUNCTION()
    void RegisterChangeStateGame(const EStateGame& NewState);

#pragma endregion

#pragma region DataController

protected:
    UPROPERTY(EditDefaultsOnly,Category = "Settings",meta = (MetaClass= "ScreenTapActor"))
    FSoftClassPath PathToScreenTap;
    
    UPROPERTY()
    AScreenTapActor* ScreenTapClass;
    
private:

    UPROPERTY()
    AStoryGMBase* StoryGM;
    
    FVector TouchLocation{FVector::ZeroVector};

#pragma endregion

#pragma region Signature

public:
    UPROPERTY(BlueprintAssignable)
    FHitActorSignature OnHitActor;

#pragma endregion

#pragma region Action

    UFUNCTION()
    void SpawnActorWithTap(FVector TapLocation);

#pragma endregion 
};
