#include "SGHUDWidget.h"
#include "SGHPBar.h"
#include "SGCrossHair.h"
#include "SGWeaponHUD.h"

bool USGHUDWidget::Initialize()
{
	bool bResult = Super::Initialize();

	bIsOnShowHPBar = false;

	return bResult;
}

void USGHUDWidget::PlayFadeInHPBarAnimation()
{
	if (!bIsOnShowHPBar)
	{
		PlayAnimation(FadeInHPBar);
	}

	bIsOnShowHPBar = true;
}

void USGHUDWidget::PlayFadeOutHPBarAnimation()
{
	if (bIsOnShowHPBar)
	{
		PlayAnimation(FadeOutHPBar);
	}

	bIsOnShowHPBar = false;
}

USGHPBar* USGHUDWidget::GetSGHPBar() const
{
	return SGHPBar;
}

USGCrossHair * USGHUDWidget::GetSGCrossHair() const
{
	return SGCrossHair;
}

USGWeaponHUD * USGHUDWidget::GetWeaponHUD() const
{
	return SGWeaponHUD;
}
