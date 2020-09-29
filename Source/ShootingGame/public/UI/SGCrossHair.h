#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGCrossHair.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGCrossHair : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetSpreadValue(float NewSpreadValue);

private:
	void SpreadCrossHair(float NewSpreadValue);

private:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Top;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Down;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Left;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Right;

	float SpreadValue;
};
