#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"
#include "PlayerService.h"
#include "SGHitEffectWidget.h"
#include "SGHUDWidget.h"
#include "SGWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(GetMesh());
	Camera->SetActive(false, false);

	bIsCrouching = false;
	bIsSprint = false;
}

void ASGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SGPlayerController = Cast<ASGPlayerController>(GetController());
	SGPlayerState = Cast<ASGPlayerState>(SGPlayerController->PlayerState);

	SGPlayerState->InitPlayerData(this);


	// 무기 장착 //

	auto MyClass = Cast<UClass>(FSoftClassPath(TEXT("/Game/BluePrint/Weapon/BP_SGDarkness_AssaultRifle.BP_SGDarkness_AssaultRifle_C")).ResolveClass());
	SGCHECK(MyClass);

	if (MyClass != nullptr)
	{
		Weapon = Cast<ASGWeapon>(GetWorld()->SpawnActor(MyClass, &FVector::ZeroVector, &FRotator::ZeroRotator));
		SGCHECK(Weapon);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
	}

	//////////////
}

void ASGPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsHealing)
	{
		if (SGPlayerState->IsMaxHP())
		{
			SGPlayerController->GetSGHUDWidget()->PlayFadeOutHPBarAnimation();
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
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"), EInputEvent::IE_Pressed, this, &ASGPlayer::Fire);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASGPlayer::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ASGPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Repeat, this, &ASGPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ASGPlayer::SprintOff);
	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ASGPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ASGPlayer::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASGPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASGPlayer::LookUp);
}

void ASGPlayer::Jump()
{
	if (bIsCrouching)
	{
		DoCrouch();
	}
	else
	{
		Super::Jump();
	}
}


int32 ASGPlayer::GetHealth() const
{
	return Health;
}

float ASGPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	SGPlayerState->SetHPToDamage(FinalDamage);
	SGPlayerController->GetSGHitEffectWidget()->PlayFadeAnimation();
	SGPlayerController->GetSGHUDWidget()->PlayFadeInHPBarAnimation();

	SetHealingTimer();

	return FinalDamage;
}

void ASGPlayer::TakeHit()
{
	FDamageEvent DamageEvent;
	TakeDamage(20, DamageEvent, GetController(), this);
}

bool ASGPlayer::IsCrouching() const
{
	return bIsCrouching;
}

bool ASGPlayer::IsSprint() const
{
	return bIsSprint;
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

void ASGPlayer::Fire()
{
	SGCHECK(Weapon);
	Weapon->Fire();
}

void ASGPlayer::DoCrouch()
{
	if (GetMovementComponent()->IsFalling() || bIsSprint)
	{
		return;
	}

	if (bIsCrouching)
	{
		bIsCrouching = false;
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::DefaultMaxWalkSpeed;
	}
	else
	{
		bIsCrouching = true;
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::CrouchMaxWalkSpeed;
	}
}

void ASGPlayer::Sprint()
{
	if (bIsSprint ||
		GetVelocity().Size() < 0 ||
		GetCharacterMovement()->IsFalling() || 
		bIsCrouching)
	{
		return;
	}

	if (!bIsSprint)
	{
		bIsSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::SprintMaxWalkSpeed;
	}
}

void ASGPlayer::SprintOff()
{
	if (bIsSprint)
	{
		bIsSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::DefaultMaxWalkSpeed;
	}
}
