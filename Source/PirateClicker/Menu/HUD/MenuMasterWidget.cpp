// This section is the property of the Dverg Verksted team


#include "Menu/HUD/MenuMasterWidget.h"

void UMenuMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    MenuGameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
}
