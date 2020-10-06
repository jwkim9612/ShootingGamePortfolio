#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGFloatingDamageText.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGFloatingDamageText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetText(FString NewDamageText);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;
};
