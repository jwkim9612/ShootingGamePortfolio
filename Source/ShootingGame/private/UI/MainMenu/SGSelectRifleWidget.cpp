#include "SGSelectRifleWidget.h"
#include "SGMainMenuPlayerController.h"
#include "Components/Button.h"

void USGSelectRifleWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USGSelectRifleWidget::OnSelectClicked()
{
	SGMainMenuPlayerController->ShowSelectPistolWidget();
}

void USGSelectRifleWidget::OnBackClicked()
{
	SGMainMenuPlayerController->ShowMainMenuWidget();
}
