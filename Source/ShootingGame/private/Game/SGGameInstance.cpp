#include "SGGameInstance.h"
#include "SGWeapon.h"

void USGGameInstance::Init()
{
	Super::Init();

	InitializeParticleDataTable();
	InitializeWeaponDataTable();
}

void USGGameInstance::InitializeParticleDataTable()
{
	SGCHECK(ParticleDataTable);

	TArray<FName> Names = ParticleDataTable->GetRowNames();
	ParticleTable.Reserve(Names.Num());
	for (const auto& Name : Names)
	{
		auto Data = ParticleDataTable->FindRow<FSGParticleData>(Name, TEXT(""));
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
	for (const auto& Name : Names)
	{
		auto Data = WeaponDataTable->FindRow<FSGWeaponData>(Name, TEXT(""));
		if (Data->WeaponPath != nullptr)
		{
			AssetLoader.LoadSynchronous(Data->WeaponPath);
			auto WeaponClass = Cast<UClass>(FSoftClassPath(Data->WeaponPath->GetPathName()).ResolveClass());
			WeaponTable.Add(Data->Name, WeaponClass);

			// �Ʒ��� ������ ���� ������ ��. SpawnActor failed because BlueprintGeneratedClass is not an actor class
			//auto WeaponSubClass = AssetLoader.LoadSynchronous(Data->WeaponPath);
			//WeaponTable.Add(Data->Name, WeaponSubClass->GetClass());
		}
	}
}

UParticleSystem * USGGameInstance::TryGetParticleSystem(FString Name)
{
	if (auto ParticleSystem = ParticleTable.Find(Name))
	{
		return *ParticleSystem;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name)
	return nullptr;
}

UClass* USGGameInstance::TryGetWeaponClass(FString Name)
{
	if (auto Weapon = WeaponTable.Find(Name))
	{
		return *Weapon;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name);
	return nullptr;
}
