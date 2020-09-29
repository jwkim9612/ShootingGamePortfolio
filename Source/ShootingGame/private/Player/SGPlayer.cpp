#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"
#include "PlayerService.h"
#include "SGHitEffectWidget.h"
#include "SGHUDWidget.h"
#include "SGWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGPlayerAnimInstance.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	ArmLengthSpeed = 2.0f;
	SetCamera(CameraMode::UnAiming);
	SetCamera(CameraMode::Stand);

	bIsCrouching = false;
	bIsSprint = false;
	bIsReloading = false;
	bIsAimDownSight = false;
}

void ASGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SGPlayerController = Cast<ASGPlayerController>(GetController());
	SGPlayerState = Cast<ASGPlayerState>(SGPlayerController->PlayerState);
	SGPlayerAnimInstance = Cast<USGPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SGPlayerState->InitPlayerData(this);


	// ���� ���� //

	auto MyClass = Cast<UClass>(FSoftClassPath(TEXT("/Game/BluePrint/Weapon/BP_SGAK47.BP_SGAK47_C")).ResolveClass());
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

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaSeconds, ArmLengthSpeed);
	SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeTransform().GetLocation(), ArmLocation, DeltaSeconds, ArmLengthSpeed));

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
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"), EInputEvent::IE_Released, this, &ASGPlayer::UnFire);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASGPlayer::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ASGPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Axis, this, &ASGPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ASGPlayer::SprintOff);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"), EInputEvent::IE_Pressed, this, &ASGPlayer::AimDownSight);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"), EInputEvent::IE_Released, this, &ASGPlayer::AimDownSightOff);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ASGPlayer::Reload);
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

float ASGPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	SGPlayerState->SetHPToDamage(FinalDamage);
	SGPlayerController->GetSGHitEffectWidget()->PlayFadeAnimation();
	SGPlayerController->GetSGHUDWidget()->PlayFadeInHPBarAnimation();

	SetHealingTimer();

	return FinalDamage;
}

int32 ASGPlayer::GetHealth() const
{
	return Health;
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

bool ASGPlayer::IsAimDownSight() const
{
	return bIsAimDownSight;
}

void ASGPlayer::MoveUpDown(float AxisValue)
{
	//AddMovementInput(Camera->GetForwardVector(), AxisValue);
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASGPlayer::MoveRightLeft(float AxisValue)
{
	//AddMovementInput(Camera->GetRightVector(), AxisValue);
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASGPlayer::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASGPlayer::LookUp(float AxisValue)
{
	float SpringArmPitchValue = SpringArm->GetRelativeTransform().Rotator().Pitch;
	if (AxisValue > 0)
	{
		if (SpringArmPitchValue > -60.0f)
		{
			SpringArm->AddRelativeRotation(FRotator(-AxisValue, 0.0f, 0.0f));
			AddControllerPitchInput(AxisValue * 0.4);
		}
	}
	else if (AxisValue < 0)
	{
		if (SpringArmPitchValue < 60.0f)
		{
			SpringArm->AddRelativeRotation(FRotator(-AxisValue, 0.0f, 0.0f));
			AddControllerPitchInput(AxisValue * 0.4);
		}
	}
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
	if (!Weapon->HasAmmo() || bIsReloading || bIsSprint)
	{
		return;
	}

	Weapon->Fire();
	Recoil();

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		if (Weapon->HasAmmo())
		{
			Weapon->Fire();
			Recoil();
		}
		else
		{
			UnFire();
		}
	}), Weapon->GetFireRate(), true);
}

void ASGPlayer::UnFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ASGPlayer::Recoil()
{
	// Pitch�� +���� �Ʒ��� -���� ������ -ó������.
	auto RecoliPitchValue = Weapon->GetRecoli();
	auto RecoliYawValue = FMath::RandRange(-RecoliPitchValue, RecoliPitchValue);

	SpringArm->AddRelativeRotation(FRotator(RecoliPitchValue, 0.0f, 0.0f));
	AddControllerPitchInput(-RecoliPitchValue * 0.4f);
	AddControllerYawInput(RecoliYawValue);
}

void ASGPlayer::Reload()
{
	if (Weapon->IsFullAmmo() || bIsReloading || bIsAimDownSight || !Weapon->HasMaxAmmo())
	{
		return;
	}

	bIsReloading = true;
	float PlayDuration = SGPlayerAnimInstance->PlayReloadAnimation();

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		Weapon->Reload();
		bIsReloading = false;
	}), PlayDuration, false);
}

void ASGPlayer::DoCrouch()
{
	if (GetMovementComponent()->IsFalling() || bIsSprint || bIsReloading)
	{
		return;
	}

	if (bIsCrouching)
	{
		bIsCrouching = false;
		SetCamera(CameraMode::Stand);
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::DefaultMaxWalkSpeed;
	}
	else
	{
		bIsCrouching = true;
		SetCamera(CameraMode::Crouch);
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::CrouchMaxWalkSpeed;
	}
}

void ASGPlayer::AimDownSight()
{
	bIsAimDownSight = true;
	SetCamera(CameraMode::Aiming);
}

void ASGPlayer::AimDownSightOff()
{
	bIsAimDownSight = false;
	SetCamera(CameraMode::UnAiming);
}

void ASGPlayer::SetCamera(CameraMode NewCameraMode)
{
	switch (NewCameraMode)
	{
	case CameraMode::UnAiming:
		ArmLengthTo = 150.0f;
		break;
	case CameraMode::Aiming:
		ArmLengthTo = 100.0f;
		break;
	case CameraMode::Stand:
		ArmLocation = FVector(0.0f, 60.0f, 70.0f);
		break;
	case CameraMode::Crouch:
		ArmLocation = FVector(0.0f, 60.0f, 20.0f);
		break;
	}
}

void ASGPlayer::Sprint()
{
	if (bIsSprint ||
		GetVelocity().Size() <= 0 || // �ڷ� �������� �� �߰��ϱ�.
		GetCharacterMovement()->IsFalling() || 
		bIsCrouching ||
		bIsReloading ||
		bIsAimDownSight)
	{
		return;
	}

	if (!bIsSprint)
	{
		SGLOG(Warning, TEXT("Sprint!!"));
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
