// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHUD.h"
#include "Components/ProgressBar.h"

void USGHUD::SetHPProgressBar(float HPRatio)
{
	SGCHECK(HPProgressBar);
	HPProgressBar->SetPercent(HPRatio);
}
