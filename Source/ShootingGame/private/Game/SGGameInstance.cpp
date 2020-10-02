#include "SGGameInstance.h"

void USGGameInstance::Init()
{
	Super::Init();

	InitializeParticleDataTable();
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

UParticleSystem * USGGameInstance::TryGetParticleSystem(FString Name)
{
	if (auto ParticleSystem = ParticleTable.Find(Name))
	{
		return *ParticleSystem;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name)
	return nullptr;
}
