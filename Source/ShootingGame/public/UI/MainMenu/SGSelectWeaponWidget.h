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

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnPreviousClicked();

private:
	void CreateWeaponButtonList();
	void UpdatePageButtonsVisibility();
	void UpdateWeaponButtons();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PreviousButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* WeaponButtonBox;

	UPROPERTY()
	TArray<class USGWeaponButton*> WeaponButtonList;

	UPROPERTY()
	class ASGMainMenuPlayerController* SGMainMenuPlayerController;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TArray<FString> WeaponNameList;

private:
	int32 CurrentPage;
	int32 PageCount;
};
