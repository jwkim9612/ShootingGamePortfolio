#include "SGProjectile.h"
#include "ProjectileService.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	
	SetRootComponent(MeshComponent);

	MovementComponent->InitialSpeed = ProjectileService::DefaultInitialSpeed;
	MovementComponent->MaxSpeed = ProjectileService::DefaultMaxSpeed;

	// 중력
	MovementComponent->ProjectileGravityScale = ProjectileService::DefaultProjectileGravityScale;

}

void ASGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// 발사체의 속도를 발사 방향으로 초기화시키는 함수입니다.
void ASGProjectile::FireInDirection(const FVector & ShootDirection)
{
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
}

void ASGProjectile::SetProjectileRotation(FRotator & WeaponRotator)
{
	MeshComponent->SetRelativeRotation(FRotator(ProjectileService::PitchValueForShape, WeaponRotator.Yaw, 0.0f));
}
