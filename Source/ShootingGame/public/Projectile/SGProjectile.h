#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGProjectile.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGProjectile();

protected:
	virtual void BeginPlay() override;

public:
	void FireInDirection(const FVector & ShootDirection);
	void SetProjectileRotation(FRotator &WeaponVector);
	void SetRotationFollowsVelocity(bool bIsOn);

	void Disable();
	void Activate();

private:
	void SetDisableTimer(float DisableTimer);
	void ClearDisableTimer();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<USceneComponent> aa;

	FTimerHandle DisableTimerHandle;

public:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
};
