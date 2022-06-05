// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TankProject/GameStructs.h>
#include "Cannon.generated.h"

UCLASS()
class TANKPROJECT_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void SpecialFire();
	bool IsReadyToFire();
	void Reload();
	void Burst();
	void Shoot();
	int GetProjectilesCount() { return ProjectilesCount; };
	void AddProjectilesCount(int value) { ProjectilesCount += value; };
	
	int GetSpecialProjectilesCount() { return SpecialProjectilesCount; };
	void AddSpecialProjectilesCount(int value) { SpecialProjectilesCount += value; };
	
	FTimerHandle ReloadTimer;
	FTimerHandle BurstTimer;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectTileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	float FireRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	float FireDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	ECannonType CannonType = ECannonType::FireProjectile;

	bool bReadyToFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	int ProjectilesCount = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	int SpecialProjectilesCount = 3;

	int BurstCount = 3;
	int CurrentBurst = 0;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	void LineTrace();
};
