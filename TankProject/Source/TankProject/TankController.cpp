// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

ATankController::ATankController()
{

}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("Rotate", this, &ATankController::RotateRight);
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankController::MoveForward(float value)
{
	TankPawn->MoveForward(value);
}

void ATankController::RotateRight(float value)
{
	TankPawn->RotateRight(value);
}
