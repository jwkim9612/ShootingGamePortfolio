#include "SGPlayerAnimInstance.h"
#include "SGPlayer.h"

void USGPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<ASGPlayer>(TryGetPawnOwner());
	SGCHECK(Player);
}

void USGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player != nullptr)
	{
		CurrentSpeed = Player->GetVelocity().Size();
		Direction = CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());
		bIsInAir = Player->GetMovementComponent()->IsFalling();
		bIsCrouching = Player->IsCrouching();
		bIsSprint = Player->IsSprint();
		bIsAimDownSight = Player->IsAimDownSight();
		bIsReloading = Player->IsReloading();
		AimRotation = GetForwardAimRotation();
	}
}

float USGPlayerAnimInstance::GetReloadLength()
{
	if(ReloadAnimMontage == nullptr)
	{
		SGLOG(Error, TEXT("ReloadAnimMontage is null!!"));
		return 0.0f;
	}

	float PlayLength = ReloadAnimMontage->GetPlayLength();
	//float PlayDuration = Montage_Play(ReloadAnimMontage);
	return PlayLength;
}

FRotator USGPlayerAnimInstance::GetForwardAimRotation()
{
	auto ControlRotation = Player->GetControlRotation();
	auto ControlPitch = ControlRotation.Pitch;
	if (ControlPitch > 180)
	{
		ControlPitch = 360 - ControlPitch;
	}
	else
	{
		ControlPitch *= -1;
	}

	ControlPitch /= 3;

	return FRotator(0.0f, 0.0f, ControlPitch);
}
