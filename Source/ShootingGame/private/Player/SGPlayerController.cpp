// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"
#include "SGHUD.h"

ASGPlayerController::ASGPlayerController()
{
	static ConstructorHelpers::FClassFinder<USGHUD> HUD_Class(TEXT("/Game/BluePrint/UI/BP_SGHUD.BP_SGHUD_C"));
	if (HUD_Class.Succeeded())
	{
		HUDWidgetClass = HUD_Class.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD Class is null!!"));
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> HitEffect_Class(TEXT("/Game/BluePrint/UI/BP_HitEffect.BP_HitEffect_C"));
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
	AddWidget(HUDWidget, HUDWidgetClass, 0);
	AddWidget(HitEffectWidget, HitEffectWidgetClass, 1);
}

// 위젯 인스턴스를 생성하고 뷰포트에 추가하는 함수
void ASGPlayerController::AddWidget(class UUserWidget* Widget, TSubclassOf<class UUserWidget>& Class, int32 ZOrder)
{
	Widget = CreateWidget<UUserWidget>(this, Class);
	if (Widget != nullptr)
	{
		Widget->AddToViewport(ZOrder);
	}
}
