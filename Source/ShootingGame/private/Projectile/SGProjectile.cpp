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

	MeshComponent->OnComponentHit.AddDynamic(this, &ASGProjectile::OnHit);
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

void ASGProjectile::SetRotationFollowsVelocity(bool bIsOn)
{
	MovementComponent->bRotationFollowsVelocity = bIsOn;
}

void ASGProjectile::Disable()
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ZeroVector);
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->Deactivate();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ASGProjectile::Activate()
{
	MovementComponent->ProjectileGravityScale = 0.05f;
	MovementComponent->Activate(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetDisableTimer(ProjectileService::DisableTimer);
}

void ASGProjectile::SetDisableTimer(float DisableTimer)
{
	GetWorld()->GetTimerManager().SetTimer(DisableTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		Disable();
	}), DisableTimer, false);
}

void ASGProjectile::ClearDisableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DisableTimerHandle);
}

void ASGProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	ACharacter* TargetActor = Cast<ACharacter>(OtherActor);
	if (TargetActor != nullptr)
	{
		SGLOG(Warning, TEXT("Hit Character %s!!"), *Hit.BoneName.ToString());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Hit.Location);
	}
	


	ClearDisableTimer();
	Disable();
}
