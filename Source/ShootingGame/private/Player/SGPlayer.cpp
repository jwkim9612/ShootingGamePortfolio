#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

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

void ASGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASGPlayer::Jump);
	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ASGPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ASGPlayer::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASGPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASGPlayer::LookUp);
}

int32 ASGPlayer::GetHealth() const
{
	return Health;
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
