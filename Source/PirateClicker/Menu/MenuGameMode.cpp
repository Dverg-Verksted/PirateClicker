// This section is the property of the Dverg Verksted team


#include "Menu/MenuGameMode.h"

void AMenuGameMode::MenuStateChange(EStateMenuMode MenuState)
{
    
    
    StateMenuMode = MenuState;
    ChangeMenuStateNotify.Broadcast(MenuState);
}
