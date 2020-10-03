#pragma once

#include "ShootingGame.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "SGType.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGType : public UObject
{
	GENERATED_BODY()
	
};


USTRUCT()
struct SHOOTINGGAME_API FSGParticleData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UParticleSystem> ParticlePath;
};

USTRUCT()
struct SHOOTINGGAME_API FSGWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ASGWeapon> WeaponPath;
};