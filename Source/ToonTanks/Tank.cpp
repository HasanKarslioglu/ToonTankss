
#include "Tank.h"

#include "ToonTankController.h"
#include "ToonTanksGameMode.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//-------------------------Constructer-----------------------// 
ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp);
}

//-------------------------Input Component-----------------------// 
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

//-------------------------Begin Play-----------------------// 
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	ToonTankController = Cast<AToonTankController>(GetController());
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

//-------------------------Tick------------------------// 
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ToonTankController)
	{
		FHitResult HitResult;
		ToonTankController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

//-------------------------Destruction-----------------------// 
void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	if (ToonTankController)
	{
		ToonTankController->SetPlayerEnabledState(false);
	}
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	if (ToonTanksGameMode)
	{
		ToonTanksGameMode->GameOver(false);
	}
}

//-------------------------Turning-----------------------// 
void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator(0);
		DeltaRotation.Yaw =  Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	
	if (deltaLocation.X < 0)
		DeltaRotation *= -1;
	
	AddActorLocalRotation(DeltaRotation, true);
}


//-------------------------Moving-----------------------// 
void ATank::Move(float Value)
{
	deltaLocation = FVector(0);
	deltaLocation.X = UGameplayStatics::GetWorldDeltaSeconds(this) * Speed * Value;
	AddActorLocalOffset(deltaLocation, true); 
}


