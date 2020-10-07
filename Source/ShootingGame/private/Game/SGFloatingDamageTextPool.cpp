#include "SGFloatingDamageTextPool.h"
#include "SGFloatingDamageText.h"
#include "Components/WidgetComponent.h"

ASGFloatingDamageTextPool::ASGFloatingDamageTextPool()
{
	FloatingDamageTextComponentPool.Reserve(20);
	for (int32 i = 0; i < 20; i++)
	{
		FString Text = FString(TEXT("FloatingDamageTextWidget"));
		FString Number = FString::FromInt(i);
		Text.Append(Number);

		auto FloatingTextWidget = CreateDefaultSubobject<UWidgetComponent>(FName(*Text));
		FloatingTextWidget->SetWidgetSpace(EWidgetSpace::Screen);
		FloatingDamageTextComponentPool.Add(FloatingTextWidget);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> FloatingDamageTextWidgetClass(TEXT("/Game/BluePrint/UI/BP_FloatingDamageText.BP_FloatingDamageText_C"));
	if (FloatingDamageTextWidgetClass.Succeeded())
	{
		for (auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
		{
			FloatingDamageTextComponent->SetWidgetClass(FloatingDamageTextWidgetClass.Class);
			FloatingDamageTextComponent->SetDrawSize(FVector2D(50.0f, 5.0f));
		}
	}

	CurrentIndex = 0;
}

void ASGFloatingDamageTextPool::BeginPlay()
{
	Super::BeginPlay();
	
	SGLOG(Warning, TEXT("BeginPlay %d"), FloatingDamageTextComponentPool.Num());

	FloatingDamageTextWidgetPool.Reserve(FloatingDamageTextComponentPool.Num());
	for (const auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
	{
		USGFloatingDamageText* SGFloatingDamageText = Cast<USGFloatingDamageText>(FloatingDamageTextComponent->GetUserWidgetObject());
		SGCHECK(SGFloatingDamageText);
		FloatingDamageTextWidgetPool.Add(SGFloatingDamageText);
	}

	for (auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
	{
		FloatingDamageTextComponent->SetVisibility(false);
	}
}

void ASGFloatingDamageTextPool::SetTextAndPlay(int32 Damage, FVector Location, bool bIsHitHead)
{
	if (CurrentIndex == 20)
	{
		CurrentIndex = 0;
	}

	auto FloatingDamageTextComponent = FloatingDamageTextComponentPool[CurrentIndex];
	FloatingDamageTextComponent->SetWorldLocation(Location);
	FloatingDamageTextComponent->SetVisibility(true);

	auto FloatingDamageTextWidget = FloatingDamageTextWidgetPool[CurrentIndex];
	FloatingDamageTextWidget->SetText(FString::FromInt(Damage), bIsHitHead);
	FloatingDamageTextWidget->PlayFadeAnimation();

	++CurrentIndex;
}
