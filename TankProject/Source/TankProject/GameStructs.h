// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
};

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Casual = 0 UMETA(DisplayName = "Casual projectile"),
	Special = 1 UMETA(DisplayName = "Special projectile"),
};

UCLASS()
class TANKPROJECT_API UGameStructs : public UObject
{
	GENERATED_BODY()
};
