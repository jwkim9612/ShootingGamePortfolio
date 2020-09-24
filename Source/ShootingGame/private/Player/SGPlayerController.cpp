// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"
#include "SGHUD.h"
#include "SGHitEffect.h"
#include "SGPlayerState.h"

ASGPlayerController::ASGPlayerController()
{
	static ConstructorHelpers::FClassFinder<USGHUD> HUD_Class(TEXT("/Game/BluePrint/UI/BP_HUD.BP_HUD_C"));
	if (HUD_Class.Succeeded())
	{
		HUDWidgetClass = HUD_Class.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD Class is null!!"));
	}

	static ConstructorHelpers::FClassFinder<USGHitEffect> HitEffect_Class(TEXT("/Game/BluePrint/UI/BP_HitEffect.BP_HitEffect_C"));
	if (HitEffect_Class.Succeeded())
	{
		HitEffectWidgetClass = HitEffect_Class.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HitEffect Class is null!!"));
	}

}

void ASGPlayerController::BeginPlay()
{
	SGPlayerState = Cast<ASGPlayerState>(PlayerState);

	HUDWidget = CreateWidget<USGHUD>(this, HUDWidgetClass);
	HUDWidget->AddToViewport(0);

	HitEffectWidget = CreateWidget<USGHitEffect>(this, HitEffectWidgetClass);
	HitEffectWidget->AddToViewport(1);

	BindWidgetToPlayerState();
}

USGHitEffect * ASGPlayerController::GetHitEffectWidget() const
{
	return HitEffectWidget;
}

void ASGPlayerController::BindWidgetToPlayerState()
{
	SGPlayerState->OnHPChanged.AddLambda([this]() -> void
	{
		HUDWidget->SetHPProgressBar(SGPlayerState->GetHPRatio());
	});
}
