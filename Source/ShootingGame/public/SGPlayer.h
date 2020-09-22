// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "SGPlayer.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ASGPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveUpDown(float AxisValue);
};
