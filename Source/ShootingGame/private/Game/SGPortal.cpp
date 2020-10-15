#include "SGPortal.h"
#include "SGPlayerController.h"
#include "SGGameInstance.h"
#include "SGHUDWidget.h"

ASGPortal::ASGPortal()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	RootComponent = CapsuleComponent;
	ParticleSystem->SetupAttachment(RootComponent);
}

void ASGPortal::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGPortal::OnOverlapBegin);

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGPlayerController = Cast<ASGPlayerController>(GetWorld()->GetFirstPlayerController());
	if (SGPlayerController != nullptr)
	{
		SGHUDWidget = SGPlayerController->GetSGHUDWidget();
	}
}

void ASGPortal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SGCHECK(SGHUDWidget);
	float AnimationLength = SGHUDWidget->PlayFadeOutScreenAnimation();

	GetWorld()->GetTimerManager().SetTimer(LoadStageTimer, FTimerDelegate::CreateLambda([this]() -> void {
		SGGameInstance->LoadNextStage();
	}), AnimationLength, false);
}
