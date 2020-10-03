#include "SGProjectile.h"
#include "SGGameInstance.h"
#include "ProjectileService.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	
	SetRootComponent(MeshComponent);
	ParticleSystemComponent->SetupAttachment(RootComponent);

	MovementComponent->InitialSpeed = ProjectileService::DefaultInitialSpeed;
	MovementComponent->MaxSpeed = ProjectileService::DefaultMaxSpeed;

	// 중력
	MovementComponent->ProjectileGravityScale = ProjectileService::DefaultProjectileGravityScale;
}

void ASGProjectile::BeginPlay()
{
	Super::BeginPlay();

	SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());
	SGCHECK(SGGameInstance);

	MeshComponent->OnComponentHit.AddDynamic(this, &ASGProjectile::OnHit);
}

// 발사체의 속도를 발사 방향으로 초기화시키는 함수입니다.
void ASGProjectile::FireInDirection(const FVector & ShootDirection)
{
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
	MeshComponent->SetRelativeRotation(ShootDirection.Rotation());
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
		auto ParticleSystem = SGGameInstance->TryGetParticleSystem(FString("HitCharacter"));
		if (ParticleSystem != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Hit.Location);
		}
	}
	else
	{
		auto ParticleSystem = SGGameInstance->TryGetParticleSystem(FString("HitWall"));
		if (ParticleSystem != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Hit.Location);
		}
	}

	ClearDisableTimer();
	Disable();
}
