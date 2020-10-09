#include "SGMainMenuPlayerController.h"
#include "SGMainMenuWidget.h"
#include "SGSelectRifleWidget.h"
#include "SGSelectPistolWidget.h"

ASGMainMenuPlayerController::ASGMainMenuPlayerController()
{
	static ConstructorHelpers::FClassFinder<USGMainMenuWidget> SGMainMenuWidget_Class(TEXT("/Game/BluePrint/UI/MainMenu/BP_MainMenu.BP_MainMenu_C"));
	if (SGMainMenuWidget_Class.Succeeded())
	{
		MainMenuWidgetClass = SGMainMenuWidget_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<USGSelectRifleWidget> SGSelectRifleWidget_Class(TEXT("/Game/BluePrint/UI/MainMenu/BP_SelectRIfle.BP_SelectRifle_C"));
	if (SGSelectRifleWidget_Class.Succeeded())
	{
		SelectRifleWidgetClass = SGSelectRifleWidget_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<USGSelectPistolWidget> SGSelectPistolWidget_Class(TEXT("/Game/BluePrint/UI/MainMenu/BP_SelectPistol.BP_SelectPistol_C"));
	if (SGSelectPistolWidget_Class.Succeeded())
	{
		SelectPistolWidgetClass = SGSelectPistolWidget_Class.Class;
	}
}

void ASGMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();
	ShowMainMenuWidget();

	bShowMouseCursor = true;

	FInputModeUIOnly Mode;
	SetInputMode(Mode);
}

void ASGMainMenuPlayerController::InitializeWidgets()
{
	SGCHECK(MainMenuWidgetClass);
	SGCHECK(SelectRifleWidgetClass);
	SGCHECK(SelectPistolWidgetClass);
	SGMainMenuWidget = CreateWidget<USGMainMenuWidget>(this, MainMenuWidgetClass);
	SGSelectRifleWidget = CreateWidget<USGSelectRifleWidget>(this, SelectRifleWidgetClass);
	SGSelectPistolWidget = CreateWidget<USGSelectPistolWidget>(this, SelectPistolWidgetClass);
}

void ASGMainMenuPlayerController::ShowMainMenuWidget()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
	}

	// ���� �� InvocationList [CurFunctionIndex]! = InDelegate ���� ������ �߰� // 
	SGMainMenuWidget = CreateWidget<USGMainMenuWidget>(this, MainMenuWidgetClass);
	//////////////////////////////////////////////////////////////////////////////

	CurrentWidget = SGMainMenuWidget;
	CurrentWidget->AddToViewport();
}

void ASGMainMenuPlayerController::ShowSelectRifleWidget()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
	}

	CurrentWidget = SGSelectRifleWidget;
	CurrentWidget->AddToViewport();
}

void ASGMainMenuPlayerController::ShowSelectPistolWidget()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
	}

	CurrentWidget = SGSelectPistolWidget;
	CurrentWidget->AddToViewport();
}
