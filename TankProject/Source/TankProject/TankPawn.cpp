// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/Actor.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"



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
	TargetRightAxisValue = value;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<ATankController>(GetController());
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Tank Movement
	FVector actorLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = actorLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds;
	SetActorLocation(movePosition, true);

	// Tank Rotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightAxisValue, RotationInterpolationKey);
	float yawRotation = CurrentRightAxisValue * RotationSpeed * DeltaSeconds;

	FRotator actorRotation = GetActorRotation();
	yawRotation += actorRotation.Yaw;
	FRotator rotation = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(rotation);

	// Turret Rotation
	if (Controller)
	{
		FVector mousePosition = Controller->GetMousePosition();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePosition);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;

		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	}
}