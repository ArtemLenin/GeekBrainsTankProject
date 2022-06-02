// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"



// Sets default values
ACannon::ACannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComponent;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectTileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ProjectTileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!IsReadyToFire()) return;
	if (ProjectilesCount <= 0) return;

	bReadyToFire = false;

	Shoot();

	ProjectilesCount--;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::SpecialFire()
{
	if (!IsReadyToFire()) return;
	if (SpecialProjectilesCount <= 0) return;

	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(BurstTimer, this, &ACannon::Burst, 1, true, 0.1f);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::Reload()
{
	bReadyToFire = true;
	CurrentBurst = 0;
}

void ACannon::Burst()
{
	CurrentBurst += 1;
	if (CurrentBurst <= BurstCount)
	{
		Shoot();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimer);
		SpecialProjectilesCount--;

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 5 / FireRate, false);
	}
}

void ACannon::Shoot()
{
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "Fire - Projectile");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectTileSpawnPoint->GetComponentLocation(), ProjectTileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "Fire - Trace");
		LineTrace();
	}
}

void ACannon::LineTrace()
{
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	FVector start = ProjectTileSpawnPoint->GetComponentLocation();
	FVector end = ProjectTileSpawnPoint->GetForwardVector() * FireRange + start;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);

		if (hitResult.Actor.Get())
		{
			hitResult.Actor.Get()->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
	}
}
