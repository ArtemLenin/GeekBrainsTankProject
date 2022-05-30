// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ACannon::ACannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComponent = RootComponent;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComponent);

	ProjectTileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ProjectTileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!IsReadyToFire()) return;
	if (ProjectilesCount <= 0) return;

	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "Fire - Projectile");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "Fire - Trace");
	}
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
		if (CannonType == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::MakeRandomColor(), "SpecialFire - Projectile", true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "SpecialFire - Trace");
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimer);
		SpecialProjectilesCount--;

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 5 / FireRate, false);
	}
}