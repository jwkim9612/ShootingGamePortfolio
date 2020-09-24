// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHPProgressBar(float HPRatio);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPProgressBar;
};
