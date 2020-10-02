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

public:
	class UParticleSystem* TryGetParticleSystem(FString Name);

public:
	FStreamableManager AssetLoader;

private:
	UPROPERTY(EditAnywhere, Category = "ParticleDataTable")
	class UDataTable* ParticleDataTable;

private:
	UPROPERTY()
	TMap<FString, class UParticleSystem*> ParticleTable;

};
