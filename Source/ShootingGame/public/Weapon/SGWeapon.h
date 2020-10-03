#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGWeapon.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGWeapon();

protected:
	virtual void BeginPlay() override;

public:
	void Fire(FVector TargetLocation);
	void Reload();
	void UseAmmo();
	void AddMaxAmmo(int32 IncreaseValue);
	bool HasAmmo() const;
	bool HasMaxAmmo() const;
	float GetFireRate() const;
	float GetRecoli() const;
	void PlayMuzzleFlash();
	bool IsFullAmmo() const;
	void PlayFireSound();
	void PlayReloadSound();

	void SetVisibility(bool bNewVisibility);

	FVector GetMuzzleLocation() const;

private:
	void CreateProjectilePool();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* FireAudioComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* ReloadAudioComponent;

	UPROPERTY(EditDefaultsOnly, category = "bullet", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 ClipSize;

	UPROPERTY(EditAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 Ammo;

	UPROPERTY(EditDefaultsOnly, Category = "bullet", meta = (AllowPrivateAccess = true))
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = "bullet", meta = (AllowPrivateAccess = true))
	float Recoli;

	UPROPERTY(EditDefaultsOnly, Category = "bullet", meta = (AllowPrivateAccess = true))
	UParticleSystem* MuzzleFlashParticle;

	UPROPERTY()
	TArray<class ASGProjectile*> ProjectilePool;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int CurrentProjectileIndex;

private:
	FVector MuzzleLocation;
	FRotator MuzzleRotation;
};
