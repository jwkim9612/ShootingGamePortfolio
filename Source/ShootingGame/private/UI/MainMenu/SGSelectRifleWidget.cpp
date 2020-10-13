#include "SGSelectRifleWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGWeaponButton.h"
#include "UIService.h"
#include "Components/Button.h"

void USGSelectRifleWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USGSelectRifleWidget::UpdateWeaponButtons()
{
	int WeaponButtonCount = FMath::Clamp(WeaponNameList.Num(), 1, UIService::MaxCountOfWeaponSelectButtonPerPage);

	for (int WeaponIndex = 0; WeaponIndex < WeaponButtonCount; ++WeaponIndex)
	{
		USGWeaponButton* WeaponButton = WeaponButtonList[WeaponIndex];
		WeaponButton->SetWeaponName(WeaponNameList[WeaponIndex + CurrentPage - 1]);
		WeaponButton->SetWeaponType(WeaponType::Rifle);
	}
}

void USGSelectRifleWidget::OnSelectClicked()
{
	SGMainMenuPlayerController->ShowSelectPistolWidget();
}

void USGSelectRifleWidget::OnBackClicked()
{
	SGMainMenuPlayerController->ShowMainMenuWidget();
}
