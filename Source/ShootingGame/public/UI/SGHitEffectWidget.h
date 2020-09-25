#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHitEffectWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHitEffectWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void PlayFadeAnimation();

private:
	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* Fade;
};
