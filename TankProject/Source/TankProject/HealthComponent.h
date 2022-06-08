// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Scorable.h"
#include "Components/ActorComponent.h"
#include "Tests/AutomationTestSettings.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UHealthComponent : public UActorComponent, public IScorable
{
	GENERATED_BODY()

	DECLARE_EVENT(UHealthComponent, FOnDie);
	DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float);
	
public:	
	UHealthComponent();

	FOnDie OnDie;
	FOnHealthChanged OnHealthChange;
	
	void TakeDamage(FDamageData);

	float GetHealth() const;
	float GetHealthState() const;

	void AddHealth(float AddHealthValue);

	void ScoreUp(FDamageData DamageData) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Value")
	float MaxHealth = 10.0f;

	UPROPERTY()
	float CurrentHealth;
};
