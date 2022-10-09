// This section is the property of the Dverg Verksted team


#include "Game/Effect/EffectManager.h"


UEffectManager::UEffectManager()
{
	PrimaryComponentTick.bCanEverTick = true;
    
}


void UEffectManager::BeginPlay()
{
	Super::BeginPlay();
    
}

void UEffectManager::ApplyFireEffect(float FireDamage, float FireDamagedDuration)
{
    //timer
    //PirateHP - FireDamage
}

void UEffectManager::ApplyIceEffect(float IceSlow, float IceSlowDuration,float PirateMoveSpeed)
{
    //timer
    //PirateMoveSpeed - IceSlow 
}


