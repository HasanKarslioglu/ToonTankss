
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "ToonTankController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{	
	ABasePawn* DeadBasePawn = Cast<ABasePawn>(DeadActor);

	if (DeadBasePawn)
	{
		DeadBasePawn->HandleDestruction();
	}
	
}
