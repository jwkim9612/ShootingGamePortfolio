#include "SGFloatingDamageText.h"
#include "Components/TextBlock.h"

void USGFloatingDamageText::SetText(FString NewDamageText)
{
	DamageText->SetText(FText::FromString(NewDamageText));
}
