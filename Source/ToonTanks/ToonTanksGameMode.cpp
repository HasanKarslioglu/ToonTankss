
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "ToonTankController.h"
#include "Turret.h"


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
		if (RemainTower == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	RemainTower = GetTowerCount();
	
	ToonTankPlayerController = Cast<AToonTankController>(UGameplayStatics::GetPlayerController(this, 0));
	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);
		FTimerHandle TH_PlayerEnable;
		FTimerDelegate TD_PlayerEnable = FTimerDelegate::CreateUObject(ToonTankPlayerController, &AToonTankController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(TH_PlayerEnable, TD_PlayerEnable, StartPlayTime,false);
	}
}

int32 AToonTanksGameMode::GetTowerCount()
{
	TArray<AActor*> TurretArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurret::StaticClass(),TurretArray );
	return TurretArray.Num();
}
