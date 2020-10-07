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
	void InitializeImageDataTable();

public:
	class UParticleSystem* TryGetParticleSystem(FString Name);
	UClass* TryGetWeaponClass(FString Name);
	class UTexture2D* TryGetImage(FString Name);

	void PlayFloatingDamageText(int32 Damage, FVector Location, bool bIsHitHead = false);

public:
	FStreamableManager AssetLoader;

private:
	UPROPERTY(EditAnywhere, Category = "ParticleDataTable")
	class UDataTable* ParticleDataTable;

	UPROPERTY(EditAnywhere, Category = "WeaponDataTable")
	class UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, Category = "ImageDataTable")
	class UDataTable* ImageDataTable;

private:
	UPROPERTY()
	TMap<FString, class UParticleSystem*> ParticleTable;

	UPROPERTY()
	TMap<FString, UClass*> WeaponTable;

	UPROPERTY()
	TMap<FString, class UTexture2D*> ImageTable;

private:
	UPROPERTY(EditAnywhere, Category = "FloatingDamageText")
	TSubclassOf<class ASGFloatingDamageTextPool> FloatingDamageTextPoolClass;

	UPROPERTY()
	class ASGFloatingDamageTextPool* FloatingDamageTextPool;
};
