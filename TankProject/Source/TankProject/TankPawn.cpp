// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/Actor.h"
#include "TankController.h"
#include "Cannon.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;

	//BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);
	
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::OnDie);
	HealthComponent->OnHealthChange.AddUObject(this, &ATankPawn::DamageTaked);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(BodyMesh);

	
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
	SetupCannon(CannonCurrentClass);
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

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::SpecialFire()
{
	if (Cannon)
	{
		Cannon->SpecialFire();
	}
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> cannonClass)
{
	if (cannonClass)
	{
		CannonCurrentClass = cannonClass;
	}

	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonCurrentClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankPawn::OnDie()
{
	Destroy();
}

void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage: %f"), *GetName(), DamageValue);
}

void ATankPawn::ChangeCannon()
{
	if (Cannon)
	{
		TSubclassOf<ACannon> temp = CannonCurrentClass;
		CannonCurrentClass = CannonSecondaryClass;
		CannonSecondaryClass = temp;

		SetupCannon(CannonCurrentClass);
	}
}
