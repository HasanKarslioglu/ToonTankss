
#include "ToonTankController.h"

void AToonTankController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
		GetPawn()->EnableInput(this);
	else
		GetPawn()->DisableInput(this);
	
	bShowMouseCursor = bPlayerEnabled; 
}
