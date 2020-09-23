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

public:
	int32 GetHealth() const;

private:
	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	//UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	//USpringArmComponent* SpringArm;

	UPROPERTY()
	class ASGPlayerController* SGPlayerController;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 Health;
};
