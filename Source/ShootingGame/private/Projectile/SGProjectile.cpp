#include "SGProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	
	SetRootComponent(MeshComponent);

	MovementComponent->InitialSpeed = 3500.0f;
	MovementComponent->MaxSpeed = 3500.0f;

	// �߷�
	MovementComponent->ProjectileGravityScale = 0.05f;

}

void ASGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// �߻�ü�� �ӵ��� �߻� �������� �ʱ�ȭ��Ű�� �Լ��Դϴ�.
void ASGProjectile::FireInDirection(const FVector & ShootDirection)
{
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
}

void ASGProjectile::SetProjectileRotation(FRotator & WeaponRotator)
{
	MeshComponent->SetRelativeRotation(FRotator(90.0f, WeaponRotator.Yaw, 0.0f));
}
