// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKPROJECT_API ATankController : public APlayerController
{
	GENERATED_BODY()
public:
	ATankController();

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePosition; };

protected:
	UPROPERTY()
	class ATankPawn* TankPawn;

	UPROPERTY()
	FVector MousePosition;

	virtual void BeginPlay() override;
	void MoveForward(float value);
	void RotateRight(float value);
	void Fire();
	void SpecialFire();
	void ChangeCannon();
};
