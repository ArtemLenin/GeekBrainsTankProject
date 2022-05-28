// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

ATankController::ATankController()
{
	bShowMouseCursor = true;
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankController::Fire);
	InputComponent->BindAction("SpecialFire", EInputEvent::IE_Pressed, this, &ATankController::SpecialFire);

}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition, mouseDirection);

	FVector PawnPosition = TankPawn->GetActorLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector dir = MousePosition - PawnPosition;
	dir.Normalize();

	MousePosition = PawnPosition + dir * 1000;
	DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Green, false, 0.1f, 0, 5);

	if (bIsShooting)
	{
		TankPawn->Fire();
	}
}

void ATankController::MoveForward(float value)
{
	TankPawn->MoveForward(value);
}

void ATankController::RotateRight(float value)
{
	TankPawn->RotateRight(value);
}

void ATankController::Fire()
{
	if (!bIsShooting)
	{
		bIsShooting = true;
		GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &ATankController::StopShoot, 3, false);
	}
}

void ATankController::SpecialFire()
{
	TankPawn->SpecialFire();
}

void ATankController::StopShoot()
{
	bIsShooting = false;
}