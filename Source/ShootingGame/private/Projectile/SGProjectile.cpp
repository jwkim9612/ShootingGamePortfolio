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

	// �߷�
	MovementComponent->ProjectileGravityScale = ProjectileService::DefaultProjectileGravityScale;

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
	MeshComponent->SetRelativeRotation(FRotator(ProjectileService::PitchValueForShape, WeaponRotator.Yaw, 0.0f));
}
