#include "SGSelectPistolWidget.h"
#include "SGMainMenuPlayerController.h"
#include "Components/Button.h"

void USGSelectPistolWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USGSelectPistolWidget::OnSelectClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("Test"));
}

void USGSelectPistolWidget::OnBackClicked()
{
	SGMainMenuPlayerController->ShowSelectRifleWidget();
}
