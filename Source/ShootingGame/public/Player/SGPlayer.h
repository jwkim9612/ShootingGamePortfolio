#pragma once

#include "ShootingGame.h"
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
	virtual void Tick(float DeltaSeconds) override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

public:
	int32 GetHealth() const;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void TakeHit();
	bool IsCrouching() const;
	bool IsSprint() const;

private:
	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	void SetHealingTimer();

	void Fire();
	void UnFire();
	void Reload();
	void DoCrouch();
	void Sprint();
	void SprintOff();

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY()
	class ASGPlayerController* SGPlayerController;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;

	UPROPERTY()
	class USGPlayerAnimInstance * SGPlayerAnimInstance;

private:
	UPROPERTY()
	class ASGWeapon* Weapon;

private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Health;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	bool bIsHealing;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsReloading;

	UPROPERTY(BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsAimDownSight;

	bool bIsCrouching;
	bool bIsSprint;


private:
	FTimerHandle HealingTimerHandle;
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
};
