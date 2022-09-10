
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(TH_FireRate, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsInFireRange())
	{
		RotateTurret(TankRef->GetActorLocation());			
	}
}

void ATurret::CheckFireCondition()
{
	if (TankRef)
	{
		float distance = FVector::Dist(GetActorLocation(), TankRef->GetActorLocation());
		if (distance <= FireDistance)
		{
			Fire();
		}
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
