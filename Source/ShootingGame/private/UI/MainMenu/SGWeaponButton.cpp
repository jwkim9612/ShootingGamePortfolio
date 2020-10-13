#include "SGWeaponButton.h"
#include "SGGameInstance.h"
#include "SGMainMenuPlayerController.h"
#include "SGSelectWeaponWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USGWeaponButton::NativeConstruct()
{
	Super::NativeConstruct();

	ChooseButton->OnClicked.AddDynamic(this, &USGWeaponButton::OnClicked);
}

void USGWeaponButton::SetWeaponName(FString NewName)
{
	Name->SetText(FText::FromString(NewName));
}

void USGWeaponButton::SetWeaponType(WeaponType NewType)
{
	Type = NewType;
}

void USGWeaponButton::OnClicked()
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());

	switch (Type)
	{
	case WeaponType::Rifle:
		SGGameInstance->SetSelectedRifleName(Name->GetText().ToString());
		break;
	case WeaponType::Pistol:
		SGGameInstance->SetSelectedPistolName(Name->GetText().ToString());
		break;
	}

	ASGMainMenuPlayerController* SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());
	USGSelectWeaponWidget* CurrentWidget = Cast<USGSelectWeaponWidget>(SGMainMenuPlayerController->GetCurrentWidget());
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->ShowSelectButton();
		CurrentWidget->SetSelectedWeaponText(Name->GetText().ToString());
		CurrentWidget->ShowSelectedWeaponText();
	}
}
