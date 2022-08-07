// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PiratePawnBase.generated.h"

UCLASS()
class PIRATECLICKER_API APiratePawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APiratePawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
