
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "ToonTankController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{	
	ABasePawn* DeadBasePawn = Cast<ABasePawn>(DeadActor);

	if (DeadBasePawn)
	{
		DeadBasePawn->HandleDestruction();
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	
	ToonTankPlayerController = Cast<AToonTankController>(UGameplayStatics::GetPlayerController(this, 0));
	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);
		FTimerHandle TH_PlayerEnable;
		FTimerDelegate TD_PlayerEnable = FTimerDelegate::CreateUObject(ToonTankPlayerController, &AToonTankController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(TH_PlayerEnable, TD_PlayerEnable, StartPlayTime,false);
	}
}
