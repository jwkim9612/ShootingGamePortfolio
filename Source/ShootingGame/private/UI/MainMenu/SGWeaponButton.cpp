#include "SGWeaponButton.h"
#include "SGGameInstance.h"
#include "SGMainMenuPlayerController.h"
#include "SGSelectWeaponWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USGWeaponButton::NativeConstruct()
{
	Super::NativeConstruct();

	ChooseButton->OnClicked.AddDynamic(this, &USGWeaponButton::OnClicked);
}

void USGWeaponButton::SetWeaponData(FSGWeaponData * WeaponData)
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());

	WeaponImage->SetBrushFromTexture(SGGameInstance->TryGetImage(WeaponData->Name));
	Name->SetText(FText::FromString(WeaponData->Name));
	MaxAmmo->SetText(FText::FromString(FString::Printf(TEXT("MaxAmmo : %d"), WeaponData->MaxAmmo)));
	ClipSize->SetText(FText::FromString(FString::Printf(TEXT("ClipSize : %d"), WeaponData->ClipSize)));
	FireRate->SetText(FText::FromString(FString::Printf(TEXT("FireRate : %.2f"), WeaponData->FireRate)));
	Recoli->SetText(FText::FromString(FString::Printf(TEXT("Recoli : %.1f"), WeaponData->Recoli)));
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
