#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGFloatingDamageTextPool.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGFloatingDamageTextPool : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGFloatingDamageTextPool();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<class UWidgetComponent*> FloatingDamageTextComponentPool;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<class USGFloatingDamageText*> FloatingDamageTextWidgetPool;
};
