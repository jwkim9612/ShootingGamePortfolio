// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerState.h"
#include "SGPlayer.h"

void ASGPlayerState::InitPlayerData(class ASGPlayer* Player)
{
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is null!!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("is not null!!"));

	int32 Health = Player->GetHealth();
	MaxHP = Health;
	CurrentHP = Health;
}

void ASGPlayerState::SetHPToDamage(int32 Damage)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0, MaxHP);

	UE_LOG(LogTemp, Warning, TEXT("Current HP : %d"), CurrentHP);
}
