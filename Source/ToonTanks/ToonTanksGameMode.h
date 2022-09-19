
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION()
	void HandleGameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool GameWinLose);

	int32 RemainTower = 0;
	int32 GetTowerCount();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
	
private:
	class AToonTankController* ToonTankPlayerController;
	
	UPROPERTY(EditAnywhere)
	float StartPlayTime = 3.f;
};
