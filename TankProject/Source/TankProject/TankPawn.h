// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKPROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();
	UFUNCTION()
	void MoveForward(float value);
	UFUNCTION()
	void RotateRight(float value);
	virtual void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void ChangeCannon();

	UFUNCTION()
	void Fire();
	UFUNCTION()
	void SpecialFire();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* TurretMesh;

	void SetupCannon(TSubclassOf<ACannon> cannonClass);
	ACannon* GetCurrentCannon(){ return Cannon; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* BodyMesh;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Rotation")
	float RotationSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Rotation")
	float RotationInterpolationKey = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Rotation")
	float TurretRotationInterpolationKey = 0.5f;

	float TargetForwardAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;
	float CurrentRightAxisValue;

	

	class ATankController* Controller;

	// Fire
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonCurrentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonSecondaryClass;
	
	UPROPERTY()
	ACannon* Cannon;


};
