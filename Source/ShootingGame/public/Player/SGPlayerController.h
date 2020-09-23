// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
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

private:
	void AddWidget(class UUserWidget* Widget, TSubclassOf<class UUserWidget>& Class, int32 ZOrder);

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> HitEffectWidgetClass;

	UPROPERTY()
	class UUserWidget* HUDWidget;

	UPROPERTY()
	class UUserWidget* HitEffectWidget;
};
