// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHitEffectWidget.h"

void USGHitEffectWidget::PlayFadeAnimation()
{
	SGCHECK(Fade);
	
	PlayAnimation(Fade);
}
