#include "SGWeaponButton.h"
#include "SGGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USGWeaponButton::NativeConstruct()
{
	Super::NativeConstruct();

	ChooseButton->OnClicked.AddDynamic(this, &USGWeaponButton::OnClicked)
}

void USGWeaponButton::SetWeaponName(FString NewName)
{
	Name->SetText(FText::FromString(NewName));
}

void USGWeaponButton::OnClicked()
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());
	//SGGameInstance->SetSe
}
