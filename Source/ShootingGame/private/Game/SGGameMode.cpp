// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameMode.h"

ASGGameMode::ASGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/Player/BP_SGPlayer"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawnBPClass is null!"));
	}

	static ConstructorHelpers::FClassFinder<APlayerController> SGPlayerControllerClass(TEXT("/Game/BluePrint/Player/BP_SGPlayerController.BP_SGPlayerController_C"));
	if (SGPlayerControllerClass.Succeeded())
	{
		PlayerControllerClass = SGPlayerControllerClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerContoller is null!"));
	}
}
