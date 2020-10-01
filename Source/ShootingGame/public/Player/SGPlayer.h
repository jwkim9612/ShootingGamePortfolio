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

	enum class CameraMode : uint8
	{
		None,
		UnAiming,
		Aiming,
		Stand,
		Crouch
	};

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	int32 GetHealth() const;
	class ASGWeapon* GetWeapon() const;

	void TakeHit();
	bool IsCrouching() const;
	bool IsSprint() const;
	bool IsAimDownSight() const;

private:
	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	void SetHealingTimer();

	void Fire();
	void FireOnCrossHair();
	void UnFire();
	void Recoil();
	void Reload();
	void DoCrouch();
	void AimDownSight();
	void AimDownSightOff();
	void SetCamera(CameraMode NewCameraMode);
	void Sprint();
	void SprintOff();
	// 후에 이름 바꿀것. // 조준선 확산 처리.
	void SpreadCorssHairSetting();
	bool IsMoving();

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

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

	bool bIsCrouching;
	bool bIsSprint;
	bool bIsAimDownSight;

	bool bIsPressedAimDownSight;
	bool bIsPressedSprint;

	float ArmLengthTo;
	float ArmLengthSpeed;
	FVector ArmLocation;

private:
	FTimerHandle HealingTimerHandle;
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
};
