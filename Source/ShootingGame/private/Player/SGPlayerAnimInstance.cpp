#include "SGPlayerAnimInstance.h"
#include "SGPlayer.h"

void USGPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<ASGPlayer>(TryGetPawnOwner());
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is null!"));
	}
}

void USGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player != nullptr)
	{
		CurrentSpeed	= Player->GetVelocity().Size();
		Direction		= CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());
		bIsInAir		= Player->GetMovementComponent()->IsFalling();
	}
}
