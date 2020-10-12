#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGWeaponButton.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGWeaponButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetWeaponName(FString NewName);

private:
	void OnClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ChooseButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
};
