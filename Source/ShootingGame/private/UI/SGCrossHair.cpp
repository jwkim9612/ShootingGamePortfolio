#include "SGCrossHair.h"
#include "Components/VerticalBox.h"

void USGCrossHair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpreadValue > 0)
	{
		SpreadValue = FMath::FInterpTo(SpreadValue, 0.0f, InDeltaTime, 3.0f);
		SpreadCrossHair(SpreadValue);
	}
}

void USGCrossHair::SetSpreadValue(float NewSpreadValue)
{
	SpreadValue = NewSpreadValue;
}

void USGCrossHair::SpreadCrossHair(float NewSpreadValue)
{
	Top->SetRenderTranslation(FVector2D(0.0f, -NewSpreadValue));
	Down->SetRenderTranslation(FVector2D(0.0f, NewSpreadValue));
	Left->SetRenderTranslation(FVector2D(-NewSpreadValue, 0.0f));
	Right->SetRenderTranslation(FVector2D(NewSpreadValue, 0.0f));
}
