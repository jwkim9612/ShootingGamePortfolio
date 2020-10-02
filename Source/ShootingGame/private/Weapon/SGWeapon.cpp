#include "SGWeapon.h"
#include "SGProjectile.h"
#include "Kismet/KismetMathLibrary.h"

ASGWeapon::ASGWeapon()
{
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
	ReloadAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadAudioComponent"));

	SetRootComponent(MeshComponent);
	FireAudioComponent->SetupAttachment(RootComponent);
	ReloadAudioComponent->SetupAttachment(RootComponent);

	ProjectilePool.Reserve(10);

	CurrentProjectileIndex = 0;

}

void ASGWeapon::BeginPlay()
{
	Super::BeginPlay();

	MuzzleLocation = MeshComponent->GetSocketLocation(TEXT("Muzzle"));
	MuzzleRotation = MeshComponent->GetSocketRotation(TEXT("Muzzle"));
	
	for (int ProjectilePoolIndex = 0; ProjectilePoolIndex < 10; ProjectilePoolIndex++)
	{
		auto Projectile = Cast<ASGProjectile>(GetWorld()->SpawnActor(ProjectileClass, &FVector::ZeroVector, &MuzzleRotation));
		if (Projectile != nullptr)
		{
			Projectile->Disable();
			ProjectilePool.Emplace(Projectile);
		}
	}
}

void ASGWeapon::Fire(FVector TargetLocation)
{
	SGCHECK(ProjectileClass);
	MuzzleLocation = MeshComponent->GetSocketLocation(TEXT("Muzzle"));
	MuzzleRotation = MeshComponent->GetSocketRotation(TEXT("Muzzle"));

	// 오브젝트 풀링 //
	auto FinalRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TargetLocation);
	FVector LaunchDirection = FinalRotation.Vector();
	if (CurrentProjectileIndex == 10)
	{
		CurrentProjectileIndex = 0;
	}

	auto CurrentProjectile = ProjectilePool[CurrentProjectileIndex];
	CurrentProjectile->SetActorLocation(MuzzleLocation);
	CurrentProjectile->FireInDirection(LaunchDirection);
	CurrentProjectile->Activate();
	PlayFireSound();
	UseAmmo();
	PlayMuzzleFlash();

	++CurrentProjectileIndex;
	//////////////////
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

void ASGWeapon::AddMaxAmmo(int32 IncreaseValue)
{
	MaxAmmo += IncreaseValue;
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

void ASGWeapon::PlayFireSound()
{
	SGCHECK(FireAudioComponent);
	FireAudioComponent->Play();
}

void ASGWeapon::PlayReloadSound()
{
	SGCHECK(ReloadAudioComponent);
	ReloadAudioComponent->Play();
}

FVector ASGWeapon::GetMuzzleLocation() const
{
	return MeshComponent->GetSocketLocation(TEXT("Muzzle"));
}
