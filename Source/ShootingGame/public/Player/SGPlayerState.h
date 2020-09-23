// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void InitPlayerData(class ASGPlayer* Player);

	void SetHPToDamage(int32 Damage);

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentHP;
};
