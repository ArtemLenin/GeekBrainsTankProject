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
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class ATankPawn* TankPawn;

	void MoveForward(float value);
};
