#include "SGWeapon.h"
#include "SGProjectile.h"

ASGWeapon::ASGWeapon()
{
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
}

void ASGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ASGWeapon::Fire()
{
	SGCHECK(ProjectileClass);
	auto MuzzleLocation = MeshComponent->GetSocketLocation(TEXT("Muzzle"));
	auto MuzzleRotation = MeshComponent->GetSocketRotation(TEXT("Muzzle"));

	auto Projectile = Cast<ASGProjectile>(GetWorld()->SpawnActor(ProjectileClass, &MuzzleLocation));
	if (Projectile != nullptr)
	{
		FVector LaunchDirection = MuzzleRotation.Vector();
		Projectile->SetProjectileRotation(MuzzleRotation);
		Projectile->FireInDirection(LaunchDirection);
	}
}
