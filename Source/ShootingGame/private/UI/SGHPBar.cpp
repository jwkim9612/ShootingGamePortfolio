// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHPBar.h"
#include "Components/ProgressBar.h"

void USGHPBar::SetHPProgressBar(float HPRatio)
{
	SGCHECK(HPProgressBar);
	HPProgressBar->SetPercent(HPRatio);
}
