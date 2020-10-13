#include "SGSelectPistolWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGWeaponButton.h"
#include "SGGameInstance.h"
#include "UIService.h"
#include "Components/Button.h"

void USGSelectPistolWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USGSelectPistolWidget::UpdateWeaponButtons()
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetGameInstance());

	int WeaponButtonCount = FMath::Clamp(WeaponNameList.Num(), 1, UIService::MaxCountOfWeaponSelectButtonPerPage);

	for (int WeaponIndex = 0; WeaponIndex < WeaponButtonCount; ++WeaponIndex)
	{
		USGWeaponButton* WeaponButton = WeaponButtonList[WeaponIndex];
		FString WeaponName = WeaponNameList[WeaponIndex + CurrentPage - 1];
		FSGWeaponData* WeaponData = SGGameInstance->TryGetWeaponData(WeaponName);
		WeaponButton->SetWeaponData(WeaponData);
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