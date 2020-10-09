#include "SGSelectWeaponWidget.h"
#include "SGMainMenuPlayerController.h"
#include "Components/Button.h"

void USGSelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());

	SelectButton->OnClicked.AddUniqueDynamic(this, &USGSelectWeaponWidget::OnSelectClicked);
	BackButton->OnClicked.AddUniqueDynamic(this, &USGSelectWeaponWidget::OnBackClicked);
}

void USGSelectWeaponWidget::OnSelectClicked()
{
	SGLOG(Warning, TEXT("Base"));
}

void USGSelectWeaponWidget::OnBackClicked()
{
	SGLOG(Warning, TEXT("Base"));
}
