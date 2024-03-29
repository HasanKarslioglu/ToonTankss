
#include "BasePawn.h"

#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

//-------------------------Constructer-----------------------// 
ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	 
	//-------------------------Creating And Attaching-----------------------// 
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectTileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectTileSpawnPoint"));
	ProjectTileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw, 0.f);
	LookAtRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),15.f);
	TurretMesh->SetWorldRotation(LookAtRotation);	
}

void ABasePawn::Fire()
{
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectTileSpawnPoint->GetComponentLocation(), ProjectTileSpawnPoint->GetComponentRotation());	
}
