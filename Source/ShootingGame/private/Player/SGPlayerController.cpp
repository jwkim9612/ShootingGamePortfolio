// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"
#include "SGHUDWidget.h"
#include "SGHitEffectWidget.h"
#include "SGPlayerState.h"
#include "SGHPBar.h"

ASGPlayerController::ASGPlayerController()
{
	static ConstructorHelpers::FClassFinder<USGHUDWidget> SGHUDWidget_Class(TEXT("/Game/BluePrint/UI/BP_SGHUDWidget.BP_SGHUDWidget_C"));
	if (SGHUDWidget_Class.Succeeded())
	{
		SGHUDWidgetClass = SGHUDWidget_Class.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidgetClass is null!!"));
	}

	static ConstructorHelpers::FClassFinder<USGHitEffectWidget> SGHitEffectWidget_Class(TEXT("/Game/BluePrint/UI/BP_SGHitEffectWidget.BP_SGHitEffectWidget_C"));
	if (SGHitEffectWidget_Class.Succeeded())
	{
		SGHitEffectWidgetClass = SGHitEffectWidget_Class.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HitEffectWidgetClass is null!!"));
	}

}

void ASGPlayerController::BeginPlay()
{
	SGPlayerState = Cast<ASGPlayerState>(PlayerState);

	SGHUDWidget = CreateWidget<USGHUDWidget>(this, SGHUDWidgetClass);
	SGHUDWidget->AddToViewport(0);

	SGHitEffectWidget = CreateWidget<USGHitEffectWidget>(this, SGHitEffectWidgetClass);
	SGHitEffectWidget->AddToViewport(1);

	BindWidgetToPlayerState();
}

USGHitEffectWidget * ASGPlayerController::GetSGHitEffectWidget() const
{
	return SGHitEffectWidget;
}

USGHUDWidget * ASGPlayerController::GetSGHUDWidget() const
{
	return SGHUDWidget;
}

void ASGPlayerController::BindWidgetToPlayerState()
{
	SGPlayerState->OnHPChanged.AddLambda([this]() -> void
	{
		SGHUDWidget->GetSGHPBar()->SetHPProgressBar(SGPlayerState->GetHPRatio());
	});
}
