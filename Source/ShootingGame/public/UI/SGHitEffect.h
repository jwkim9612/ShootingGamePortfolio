// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHitEffect : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void PlayFadeAnimation();

private:
	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* Fade;
};
