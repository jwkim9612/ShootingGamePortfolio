#include "SGHitEffectWidget.h"

void USGHitEffectWidget::PlayFadeAnimation()
{
	SGCHECK(Fade);
	
	PlayAnimation(Fade);
}
