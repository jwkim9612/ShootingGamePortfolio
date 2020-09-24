// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

public:
	void PlayFadeInHPBarAnimation();
	void PlayFadeOutHPBarAnimation();

	class USGHPBar* GetSGHPBar() const;

private:
	UPROPERTY(meta = (BindWidget))
	class USGHPBar* SGHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutHPBar;

private:
	bool bIsOnShowHPBar;
};
