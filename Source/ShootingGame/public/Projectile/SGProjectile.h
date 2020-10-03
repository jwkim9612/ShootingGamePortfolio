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

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	FTimerHandle DisableTimerHandle;
};
