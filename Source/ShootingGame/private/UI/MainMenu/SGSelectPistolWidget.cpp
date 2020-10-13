#include "SGSelectPistolWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGWeaponButton.h"
#include "UIService.h"
#include "Components/Button.h"

void USGSelectPistolWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USGSelectPistolWidget::UpdateWeaponButtons()
{
	int WeaponButtonCount = FMath::Clamp(WeaponNameList.Num(), 1, UIService::MaxCountOfWeaponSelectButtonPerPage);

	for (int WeaponIndex = 0; WeaponIndex < WeaponButtonCount; ++WeaponIndex)
	{
		USGWeaponButton* WeaponButton = WeaponButtonList[WeaponIndex];
		WeaponButton->SetWeaponName(WeaponNameList[WeaponIndex + CurrentPage - 1]);
		WeaponButton->SetWeaponType(WeaponType::Pistol);
	}
}

void USGSelectPistolWidget::OnSelectClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("Test"));
}

void USGSelectPistolWidget::OnBackClicked()
{
	SGMainMenuPlayerController->ShowSelectRifleWidget();
}
