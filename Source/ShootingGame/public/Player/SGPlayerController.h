#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASGPlayerController();

	virtual void BeginPlay() override;

public:
	class USGHitEffectWidget* GetSGHitEffectWidget() const;
	class USGHUDWidget* GetSGHUDWidget() const;

private:
	void BindWidgetToPlayerState();

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> SGHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> SGHitEffectWidgetClass;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;

	UPROPERTY()
	class USGHUDWidget* SGHUDWidget;

	UPROPERTY()
	class USGHitEffectWidget* SGHitEffectWidget;
};
