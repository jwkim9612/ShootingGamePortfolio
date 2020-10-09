#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGSelectWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGSelectWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	virtual void OnSelectClicked();

	UFUNCTION()
	virtual void OnBackClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY()
	class ASGMainMenuPlayerController* SGMainMenuPlayerController;
};
