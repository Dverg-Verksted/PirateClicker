// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Game/AI/Effect/EffectDataTypes.h"
#include "TotemDataAsset.generated.h"

class UNiagaraSystem;
/**
 *
 */
UCLASS(NotBlueprintable, NotBlueprintType)
class PIRATECLICKER_API UTotemDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // @public Totem mesh
    UPROPERTY(EditAnywhere, Category = "Settings totem", meta = (DisplayName = "Мэш тотема"))
    UStaticMesh* TotemMesh{nullptr};

    UPROPERTY(EditAnywhere, Category = "Settings totem", meta = (DisplayName = "Эффект тотема"))
    UNiagaraSystem* TotemParticle;

    UPROPERTY(EditAnywhere, Category = "Settings totem", meta = (DisplayName = "Данные по эффекту наложения", ShowOnlyInnerProperties))
    FDataEffect DataEffect;
};
