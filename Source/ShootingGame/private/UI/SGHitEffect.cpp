// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHitEffect.h"

void USGHitEffect::PlayFadeAnimation()
{
	if (Fade != nullptr)
	{
		PlayAnimation(Fade);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fade Animation is null!!"));
	}
}
