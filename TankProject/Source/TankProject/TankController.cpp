// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"

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
	InputComponent->BindAction("ChangeCannon", EInputEvent::IE_Pressed, this, &ATankController::ChangeCannon);

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
	FVector PawnPosition;
	if(TankPawn) PawnPosition = TankPawn->GetActorLocation();
	//if(TankPawn) PawnPosition = TankPawn->GetCannonSetupPoint()->GetComponentLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector dir = MousePosition - PawnPosition;
	dir.Normalize();

	MousePosition = PawnPosition + dir * 1000;
	DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Green, false, 0.1f, 0, 5);
	//DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Green, false, 0.1f, 0, 5);
}

void ATankController::MoveForward(float value)
{
	if (TankPawn)
	TankPawn->MoveForward(value);
}

void ATankController::RotateRight(float value)
{
	if (TankPawn)
	TankPawn->RotateRight(value);
}

void ATankController::Fire()
{
	if (TankPawn) TankPawn->Fire();
}

void ATankController::SpecialFire()
{
	if (TankPawn) TankPawn->SpecialFire();
}

void ATankController::ChangeCannon()
{
	if (TankPawn) TankPawn->ChangeCannon();
}