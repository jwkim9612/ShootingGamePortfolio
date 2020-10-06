#include "SGPlayerController.h"
#include "SGHUDWidget.h"
#include "SGHitEffectWidget.h"
#include "SGPlayerState.h"
#include "SGHPBar.h"
#include "SGCrossHair.h"

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

void ASGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);

	SGPlayerState = Cast<ASGPlayerState>(PlayerState);
	SGCHECK(SGPlayerState);

	SGCHECK(SGHUDWidgetClass);
	SGHUDWidget = CreateWidget<USGHUDWidget>(this, SGHUDWidgetClass);
	SGHUDWidget->AddToViewport(0);
	SGHUDWidget->SetControllingPawn(aPawn);

	SGCHECK(SGHitEffectWidgetClass);
	SGHitEffectWidget = CreateWidget<USGHitEffectWidget>(this, SGHitEffectWidgetClass);
	SGHitEffectWidget->AddToViewport(1);

	BindWidgetToPlayerState();

	SGLOG(Warning, TEXT("Possess Controller"));
}

void ASGPlayerController::BeginPlay()
{
	//SGPlayerState = Cast<ASGPlayerState>(PlayerState);
	//SGCHECK(SGPlayerState);

	//SGCHECK(SGHUDWidgetClass);
	//SGHUDWidget = CreateWidget<USGHUDWidget>(this, SGHUDWidgetClass);
	//SGHUDWidget->AddToViewport(0);

	//SGCHECK(SGHitEffectWidgetClass);
	//SGHitEffectWidget = CreateWidget<USGHitEffectWidget>(this, SGHitEffectWidgetClass);
	//SGHitEffectWidget->AddToViewport(1);

	//BindWidgetToPlayerState();

	SGLOG(Warning, TEXT("Begin Controller"));
}

USGHitEffectWidget * ASGPlayerController::GetSGHitEffectWidget() const
{
	return SGHitEffectWidget;
}

USGHUDWidget * ASGPlayerController::GetSGHUDWidget() const
{
	return SGHUDWidget;
}

void ASGPlayerController::SetDefaultSpreadCrossHair(float SpreadValue)
{
	auto CrossHair = SGHUDWidget->GetSGCrossHair();
	SGCHECK(CrossHair);
	CrossHair->SetDefaultSpreadValue(SpreadValue);
}

void ASGPlayerController::SetCurrentSpreadCrossHair(float SpreadValue)
{
	auto CrossHair = SGHUDWidget->GetSGCrossHair();
	SGCHECK(CrossHair);
	CrossHair->SetCurrentSpreadValue(SpreadValue);
}

void ASGPlayerController::BindWidgetToPlayerState()
{
	SGPlayerState->OnHPChanged.AddLambda([this]() -> void
	{
		SGHUDWidget->GetSGHPBar()->SetHPProgressBar(SGPlayerState->GetHPRatio());
	});
}
