#include "SGProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	
	SetRootComponent(MeshComponent);

	MovementComponent->InitialSpeed = 3500.0f;
	MovementComponent->MaxSpeed = 3500.0f;

	// 중력
	MovementComponent->ProjectileGravityScale = 0.05f;

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
	MeshComponent->SetRelativeRotation(FRotator(90.0f, WeaponRotator.Yaw, 0.0f));
}
