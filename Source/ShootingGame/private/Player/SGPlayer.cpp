#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"
#include "PlayerService.h"
#include "SGHitEffectWidget.h"
#include "SGHUDWidget.h"
#include "SGWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGPlayerAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "SGCrossHair.h"
#include "Kismet/KismetMathLibrary.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
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


	// 무기 장착 //

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

ASGWeapon * ASGPlayer::GetWeapon() const
{
	return Weapon;
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

	FireOnCrossHair();
	
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		if (Weapon->HasAmmo())
		{
			FireOnCrossHair();
		}
		else
		{
			UnFire();
		}
	}), Weapon->GetFireRate(), true);
}

void ASGPlayer::FireOnCrossHair()
{
	float SpreadValue = SGPlayerController->GetSGHUDWidget()->GetSGCrossHair()->GetSpreadValue();
	float RandomYawValue = FMath::RandRange(-SpreadValue, SpreadValue) * 0.1f;
	float RandomPitchValue = FMath::RandRange(-SpreadValue, SpreadValue) * 0.1f;
	FRotator FinalRotation = UKismetMathLibrary::ComposeRotators(FRotator(RandomPitchValue, RandomYawValue, 0.0f), Camera->GetComponentToWorld().GetRotation().Rotator());
	FVector FinalVector = UKismetMathLibrary::GetForwardVector(FinalRotation);

	FHitResult HitResult;
	auto Start = Camera->GetComponentToWorld().GetLocation();
	auto End = FinalVector * 100000 + Start;

	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f, ESceneDepthPriorityGroup::SDPG_World, 2.0f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
	{
		Weapon->Fire(HitResult.ImpactPoint);
		Recoil();
		SpreadCorssHairSetting();
	}
	else
	{
		Weapon->Fire(HitResult.ImpactPoint);
		Recoil();
		SpreadCorssHairSetting();
	}
}

void ASGPlayer::UnFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ASGPlayer::Recoil()
{
	// Pitch는 +값이 아래고 -값이 위여서 -처리해줌.
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
		GetVelocity().Size() <= 0 || // 뒤로 움직였을 때 추가하기.
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

void ASGPlayer::SpreadCorssHairSetting()
{
	if (bIsAimDownSight)
	{
		if (IsMoving())
		{
			SGPlayerController->SetSpreadCrossHair(40.0f);
		}
		else
		{
			SGPlayerController->SetSpreadCrossHair(20.0f);
		}
	}
	else
	{
		if (IsMoving())
		{
			SGPlayerController->SetSpreadCrossHair(70.0f);
		}
		else
		{
			SGPlayerController->SetSpreadCrossHair(50.0f);
		}
	}
}

bool ASGPlayer::IsMoving()
{
	if (GetCharacterMovement()->Velocity.Size() > 0)
	{
		return true;
	}

	return false;
}
