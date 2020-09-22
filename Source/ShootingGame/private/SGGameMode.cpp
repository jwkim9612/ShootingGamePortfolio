// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameMode.h"

ASGGameMode::ASGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/Player/MySGPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawnBPClass is NULL!"));
	}
}