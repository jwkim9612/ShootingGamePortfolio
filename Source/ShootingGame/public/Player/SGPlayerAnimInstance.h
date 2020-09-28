#pragma once

#include "ShootingGame.h"
#include "Animation/AnimInstance.h"
#include "SGPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()



private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	float PlayReloadAnimation();

private:
	FRotator GetForwardAimRotation();

private:
	UPROPERTY()
	class ASGPlayer* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsCrouching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsAimDownSight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	FRotator AimRotation;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	UAnimMontage* ReloadAnimMontage;
};
