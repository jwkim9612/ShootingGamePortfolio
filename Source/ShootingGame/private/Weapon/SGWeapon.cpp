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
	MuzzleLocation = MeshComponent->GetSocketLocation(TEXT("Muzzle"));
	MuzzleRotation = MeshComponent->GetSocketRotation(TEXT("Muzzle"));

	auto Projectile = Cast<ASGProjectile>(GetWorld()->SpawnActor(ProjectileClass, &MuzzleLocation));
	if (Projectile != nullptr)
	{
		FVector LaunchDirection = MuzzleRotation.Vector();
		Projectile->SetProjectileRotation(MuzzleRotation);
		Projectile->FireInDirection(LaunchDirection);
		UseAmmo();
		PlayMuzzleFlash();
	}
}

void ASGWeapon::Reload()
{
	if (IsFullAmmo())
	{
		return;
	}

	int32 ReloadValues = ClipSize - Ammo;
	if (ReloadValues > MaxAmmo)
	{
		Ammo += MaxAmmo;
		MaxAmmo = 0;
	}
	else
	{
		MaxAmmo -= ReloadValues;
		Ammo += ReloadValues;
	}
}

void ASGWeapon::UseAmmo()
{
	if (Ammo > 0)
	{
		--Ammo;
	}
}

bool ASGWeapon::HasAmmo() const
{
	if (Ammo > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ASGWeapon::HasMaxAmmo() const
{
	if (MaxAmmo > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float ASGWeapon::GetFireRate() const
{
	return FireRate;
}

float ASGWeapon::GetRecoli() const
{
	return Recoli;
}

void ASGWeapon::PlayMuzzleFlash()
{
	SGCHECK(MuzzleFlashParticle);
	auto MuzzleFlash = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlashParticle, MuzzleLocation, MuzzleRotation);
	// 파티클 크기가 너무 커서 일단 Scale을 0.1f로 줄임
	//MuzzleFlash->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
}

bool ASGWeapon::IsFullAmmo() const
{
	if (Ammo == ClipSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}
