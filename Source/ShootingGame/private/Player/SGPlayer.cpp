#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"
#include "PlayerService.h"
#include "SGHitEffect.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(GetMesh());
	Camera->SetActive(false, false);
}

void ASGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SGPlayerController = Cast<ASGPlayerController>(GetController());
	SGPlayerState = Cast<ASGPlayerState>(SGPlayerController->PlayerState);

	SGPlayerState->InitPlayerData(this);
}

void ASGPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsHealing)
	{
		if (SGPlayerState->IsMaxHP())
		{
			bIsHealing = false;
		}
		else
		{
			SGPlayerState->HealHP();
		}
	}
}

void ASGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASGPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Hit"), EInputEvent::IE_Pressed, this, &ASGPlayer::TakeHit);
	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ASGPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ASGPlayer::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASGPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASGPlayer::LookUp);
}

int32 ASGPlayer::GetHealth() const
{
	return Health;
}

float ASGPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	SGPlayerState->SetHPToDamage(FinalDamage);
	SGPlayerController->GetHitEffectWidget()->PlayFadeAnimation();

	SetHealingTimer();

	return FinalDamage;
}

void ASGPlayer::TakeHit()
{
	FDamageEvent DamageEvent;
	TakeDamage(20, DamageEvent, GetController(), this);
}

void ASGPlayer::MoveUpDown(float AxisValue)
{
	AddMovementInput(Camera->GetForwardVector(), AxisValue);
}

void ASGPlayer::MoveRightLeft(float AxisValue)
{
	AddMovementInput(Camera->GetRightVector(), AxisValue);
}

void ASGPlayer::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASGPlayer::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ASGPlayer::SetHealingTimer()
{
	bIsHealing = false;

	GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HealingTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		bIsHealing = true;
	}), PlayerService::HealingTimer, false);
}
