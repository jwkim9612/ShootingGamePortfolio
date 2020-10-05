#include "SGWeaponHUD.h"
#include "SGWeapon.h"
#include "Components/TextBlock.h"

void USGWeaponHUD::Update()
{
	Ammo->SetText(FText::FromString(FString::FromInt(CurrentWeapon->GetAmmo())));
	MaxAmmo->SetText(FText::FromString(FString::FromInt(CurrentWeapon->GetMaxAmmo())));
}

void USGWeaponHUD::SetCurrentWeapon(class ASGWeapon* NewWeapon)
{
	SGCHECK(NewWeapon);
	CurrentWeapon = NewWeapon;
}
