// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Cannon.h"
#include "HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/UObjectGlobals.h"


ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Collision"));
	HitCollision->SetupAttachment(BodyMesh);

	UStaticMesh* bodyMesh = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMesh) BodyMesh->SetStaticMesh(bodyMesh);

	UStaticMesh* turretMesh = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMesh) TurretMesh->SetStaticMesh(turretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::OnDie);
	HealthComponent->OnHealthChange.AddUObject(this, &ATurret::DamageTaked);
}

void ATurret::DamageTaked(float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage : %f Health : %f"), *GetName(), Damage, HealthComponent->GetHealth());
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon();
	Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
}

void ATurret::Destroyed()
{
	if (Cannon) Cannon->Destroy();
}

void ATurret::Targeting()
{
	if (IsPlayerRange()) RotateToPlayer();
	if (Cannon && CanFire() && Cannon->IsReadyToFire()) Fire();
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Pawn->GetActorLocation());
	FRotator currentRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation, targetRotation, TargetingSpeed));
}

bool ATurret::IsPlayerRange()
{
	return FVector::Distance(GetActorLocation(), Pawn->GetActorLocation()) <= TargetingRange; 
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = Pawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurence;
}

void ATurret::Fire()
{
	if (Cannon) Cannon->Fire();
}

void ATurret::SetupCannon()
{
	if (!CannonClass) UE_LOG(LogTemp, Warning, TEXT("Cannon class is null"));
	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATurret::OnDie()
{
	Destroy();
}

