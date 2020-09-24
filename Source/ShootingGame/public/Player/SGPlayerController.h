// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASGPlayerController();

	virtual void BeginPlay() override;

public:
	class USGHitEffect* GetHitEffectWidget() const;

private:
	void BindWidgetToPlayerState();

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> HitEffectWidgetClass;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;

	UPROPERTY()
	class USGHUD* HUDWidget;

	UPROPERTY()
	class USGHitEffect* HitEffectWidget;
};
