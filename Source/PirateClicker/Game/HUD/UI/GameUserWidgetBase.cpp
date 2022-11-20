// This section is the property of the Dverg Verksted team

#include "Game/HUD/UI/GameUserWidgetBase.h"

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ETotems"))
int32 TotemFlags = 0;

UFUNCTION(BlueprintCallable)
bool IsFire()
{
    return TotemFlags & (uint8)ETotems::Fire;
}

UFUNCTION(BlueprintCallable)
bool IsFrost()
{
    return TotemFlags & (uint8)ETotems::Frost;
}

UFUNCTION(BlueprintCallable)
bool IsThirdType()
{
    return TotemFlags & (uint8)ETotems::ThirdType;
}

UFUNCTION(BlueprintCallable)
bool IsFourthType()
{
    return TotemFlags & (uint8)ETotems::FourthType;
}

void UGameUserWidgetBase::SetTotemsToHUD(int32 Totems, bool& Fire, bool& Frost, bool& ThirdType, bool& FourthType) 
{
    TotemFlags = Totems;
    Fire = IsFire();
    Frost = IsFrost();
    ThirdType = IsThirdType();
    FourthType = IsFourthType();
}
