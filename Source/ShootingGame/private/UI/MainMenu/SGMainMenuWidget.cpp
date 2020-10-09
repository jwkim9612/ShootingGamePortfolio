#include "SGMainMenuWidget.h"
#include "SGMainMenuPlayerController.h"
#include "Components/Button.h"

void USGMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());

	NewGameButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnNewGameClicked);
	ContinueButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnContinueClicked);
	ExitButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnExitClicked);
}

void USGMainMenuWidget::OnNewGameClicked()
{
	SGMainMenuPlayerController->ShowSelectRifleWidget();
}

void USGMainMenuWidget::OnContinueClicked()
{
	SGLOG(Warning, TEXT("Continue"));
}

void USGMainMenuWidget::OnExitClicked()
{
	SGLOG(Warning, TEXT("Exit"));
}
