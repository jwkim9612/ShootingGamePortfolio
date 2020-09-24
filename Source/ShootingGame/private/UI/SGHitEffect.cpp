// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHitEffect.h"

void USGHitEffect::PlayFadeAnimation()
{
	SGCHECK(Fade);
	
	PlayAnimation(Fade);
}
