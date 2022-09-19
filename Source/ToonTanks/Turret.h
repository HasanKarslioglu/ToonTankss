// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();
		
protected:
	virtual void BeginPlay() override;

private:
	class ATank* TankRef;
	
	UPROPERTY(EditAnywhere)
	float FireDistance = 800.f;
	
	FTimerHandle TH_FireRate;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool IsInFireRange();

	class AToonTanksGameMode* ToonTanksGameMode;
};

