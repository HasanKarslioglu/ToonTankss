
#pragma once
#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();
	
protected:

	virtual void BeginPlay() override;
	void Move(float Value);
	void Turn(float Value);
	
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess="true"));
	int Speed = 400.f;
	
	FVector deltaLocation;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess="true"));
	int TurnRate = 45.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	class AToonTankController* ToonTankController;

	class AToonTanksGameMode* ToonTanksGameMode;
};



