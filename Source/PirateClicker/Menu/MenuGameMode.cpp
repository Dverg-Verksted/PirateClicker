// This section is the property of the Dverg Verksted team


#include "Menu/MenuGameMode.h"

void AMenuGameMode::MenuStateChange(EStateMenuMode MenuState)
{
    StateMenuMode = MenuState;
    OnChangeMenuStateNotify.Broadcast(MenuState);
}

EStateMenuMode AMenuGameMode::GetCurrentMenuState()
{
    return StateMenuMode;
}
