// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooter.generated.h"

UCLASS()
class TANKPROJECT_API AShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	AShooter();
    
    UFUNCTION()
	void Fire();	

	TSubclassOf<ACannon> GetCannonCurrentClass(){ return CannonCurrentClass; }

	UFUNCTION()
	void TakeDamage(FDamageData DamageData) override;

	UFUNCTION()
	void OnDie();

	UFUNCTION()
	void DamageTaked(float DamageValue);

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollision;
	
	// Fire
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonCurrentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonSecondaryClass;
	
	UPROPERTY()
	ACannon* Cannon;

	void SetupCannon(TSubclassOf<ACannon> cannonClass);

	const FString BodyMeshPath;
	const FString TurretMeshPath;

};
