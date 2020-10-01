#include "SGProjectile.h"
#include "ProjectileService.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	
	SetRootComponent(MeshComponent);
	AudioComponent->SetupAttachment(RootComponent);


	MovementComponent->InitialSpeed = ProjectileService::DefaultInitialSpeed;
	MovementComponent->MaxSpeed = ProjectileService::DefaultMaxSpeed;

	// �߷�
	MovementComponent->ProjectileGravityScale = ProjectileService::DefaultProjectileGravityScale;

}

void ASGProjectile::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &ASGProjectile::OnHit);
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

void ASGProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* TargetActor = Cast<ACharacter>(OtherActor);
	if (TargetActor != nullptr)
	{
		SGLOG(Warning, TEXT("Hit Character %s!!"), *Hit.BoneName.ToString());
	}
}