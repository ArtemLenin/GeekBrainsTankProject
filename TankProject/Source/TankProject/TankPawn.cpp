// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/Actor.h"


// Sets default values
ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::MoveForward(float value)
{
	TargetForwardAxisValue = value;
}

void ATankPawn::RotateRight(float value)
{
	TargetRotateAxisValue = value;
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector actorLocation = GetActorLocation();
	FRotator actorRotation = GetActorRotation();
	FVector forwardVector = GetActorForwardVector();

	FVector movePosition = actorLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds;
	FRotator rotation = actorRotation + FRotator(0, RotationSpeed, 0) * RotationSpeed * TargetRotateAxisValue * DeltaSeconds;
	SetActorLocation(movePosition, true);
	SetActorRotation(rotation);
}
