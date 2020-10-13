#include "SGGameInstance.h"
#include "SGFloatingDamageTextPool.h"
#include "SGWeapon.h"

void USGGameInstance::Init()
{
	Super::Init();

	InitializeParticleDataTable();
	InitializeWeaponDataTable();
	InitializeImageDataTable();
}

void USGGameInstance::SetSelectedRifleName(FString RifleName)
{
	SelectedRifleName = RifleName;
}

void USGGameInstance::SetSelectedPistolName(FString PistolName)
{
	SelectedPistolName = PistolName;
}

FString USGGameInstance::GetSelectedRifleName() const
{
	return SelectedRifleName;
}

FString USGGameInstance::GetSelectedPistolName() const
{
	return SelectedPistolName;
}

void USGGameInstance::InitializeParticleDataTable()
{
	SGCHECK(ParticleDataTable);

	TArray<FName> Names = ParticleDataTable->GetRowNames();
	ParticleTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGParticleData* Data = ParticleDataTable->FindRow<FSGParticleData>(Name, TEXT(""));
		if (!Data->ParticlePath.IsNull())
		{
			ParticleTable.Add(Data->Name, AssetLoader.LoadSynchronous(Data->ParticlePath));
		}
	}
}

void USGGameInstance::InitializeWeaponDataTable()
{
	SGCHECK(WeaponDataTable);

	TArray<FName> Names = WeaponDataTable->GetRowNames();
	WeaponTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGWeaponData* Data = WeaponDataTable->FindRow<FSGWeaponData>(Name, TEXT(""));
		if (Data->Class != nullptr)
		{
			ASGWeapon* Weapon = Data->Class->GetDefaultObject<ASGWeapon>();
			Weapon->SetWeaponData(Data);

			WeaponTable.Add(Data->Name, *Data);
			//AssetLoader.LoadSynchronous(Data->WeaponPath);
			//UClass* WeaponClass = Cast<UClass>(FSoftClassPath(Data->WeaponPath->GetPathName()).ResolveClass());
			//WeaponTable.Add(Data->Name, WeaponClass);

			// 아래는 다음과 같은 오류가 뜸. SpawnActor failed because BlueprintGeneratedClass is not an actor class
			//auto WeaponSubClass = AssetLoader.LoadSynchronous(Data->WeaponPath);
			//WeaponTable.Add(Data->Name, WeaponSubClass->GetClass());
		}
	}
}

void USGGameInstance::InitializeImageDataTable()
{
	SGCHECK(ImageDataTable);

	TArray<FName> Names = ImageDataTable->GetRowNames();
	ImageTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGImageData* Data = ImageDataTable->FindRow<FSGImageData>(Name, TEXT(""));
		if (!Data->ImagePath.IsNull())
		{
			ImageTable.Add(Data->Name, AssetLoader.LoadSynchronous(Data->ImagePath));
		}
	}
}

void USGGameInstance::CreateFloatingDamageTextPool()
{
	FloatingDamageTextPool = GetWorld()->SpawnActor<ASGFloatingDamageTextPool>(FloatingDamageTextPoolClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

UParticleSystem * USGGameInstance::TryGetParticleSystem(FString Name)
{
	if (UParticleSystem** ParticleSystem = ParticleTable.Find(Name))
	{
		return *ParticleSystem;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name)
	return nullptr;
}

FSGWeaponData* USGGameInstance::TryGetWeaponData(FString Name)
{
	if (FSGWeaponData* Data = WeaponTable.Find(Name))
	{
		return Data;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name);
	return nullptr;
}

UTexture2D* USGGameInstance::TryGetImage(FString Name)
{
	if (UTexture2D** Image = ImageTable.Find(Name))
	{
		return *Image;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name);
	return nullptr;
}

void USGGameInstance::PlayFloatingDamageText(int32 Damage, FVector Location, bool bIsHitHead)
{
	FloatingDamageTextPool->SetTextAndPlay(Damage, Location, bIsHitHead);
}
