// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float TakeDamageValue = DamageData.DamageValue;
	CurrentHealth -= TakeDamageValue;

	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())
		{
			ScoreUp(DamageData);
			OnDie.Broadcast();
		}
	}
	else
	{
		if (OnHealthChange.IsBound())
		{
			OnHealthChange.Broadcast(TakeDamageValue);
		}
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::AddHealth(float AddHealthValue)
{
	CurrentHealth += AddHealthValue;
	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
}

void ScoreUp(FDamageData DamageData)
{
	
}