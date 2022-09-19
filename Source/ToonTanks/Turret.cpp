
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(TH_FireRate, this, &ATurret::CheckFireCondition, FireRate, true);
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsInFireRange())
	{
		RotateTurret(TankRef->GetActorLocation());			
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	if (ToonTanksGameMode)
	{
		ToonTanksGameMode->RemainTower -= 1; 
	}
	Destroy();
}

void ATurret::CheckFireCondition()
{
	if (TankRef == nullptr)
	{
		return;
	}
	if (IsInFireRange() && TankRef->bAlive)
	{
		Fire();
	}
	
}

bool ATurret::IsInFireRange()
{
	if (TankRef)
	{
		float distance = FVector::Dist(GetActorLocation(), TankRef->GetActorLocation());
		if (distance <= FireDistance)
			return true;
	}
	return false;
}
