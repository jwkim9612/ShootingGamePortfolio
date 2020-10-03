#pragma once

#include "ShootingGame.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "SGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init() override;

private:
	void InitializeParticleDataTable();
	void InitializeWeaponDataTable();

public:
	class UParticleSystem* TryGetParticleSystem(FString Name);
	UClass* TryGetWeaponClass(FString Name);

public:
	FStreamableManager AssetLoader;

private:
	UPROPERTY(EditAnywhere, Category = "ParticleDataTable")
	class UDataTable* ParticleDataTable;

	UPROPERTY(EditAnywhere, Category = "WeaponDataTable")
	class UDataTable* WeaponDataTable;

private:
	UPROPERTY()
	TMap<FString, class UParticleSystem*> ParticleTable;

	UPROPERTY()
	TMap<FString, UClass*> WeaponTable;
};
