// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
UCLASS()
class TANKPROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();
	void MoveForward(float value);
	void RotateRight(float value);
	void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh");
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh");
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components");
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components");
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed");
	float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Rotation");
	float RotationSpeed = 10.0f;

	float Test = 1.0f;

	float TargetForwardAxisValue = 0.0f;
	float TargetRotateAxisValue = 0.0f;
};
