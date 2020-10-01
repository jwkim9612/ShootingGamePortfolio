#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGAICharacter.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY()
	class ASGAIController* SGAIController;

private:
	UPROPERTY(EditAnywhere, category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Health;
};
