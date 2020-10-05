#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGWeaponHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGWeaponHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Update();
	void SetCurrentWeapon(class ASGWeapon* NewWeapon);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Ammo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	class UImage* WeaponImage;

private:
	UPROPERTY()
	class ASGWeapon* CurrentWeapon;
};
