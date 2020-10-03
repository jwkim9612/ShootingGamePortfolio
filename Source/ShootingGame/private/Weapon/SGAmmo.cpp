#include "SGAmmo.h"
#include "SGPlayer.h"
#include "SGWeapon.h"

ASGAmmo::ASGAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	StaticMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ASGAmmo::OnOverlapBegin);
}

void ASGAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGAmmo::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto SGPlayer = Cast<ASGPlayer>(OtherActor);
	if (SGPlayer != nullptr)
	{
		SGPlayer->GetCurrentWeapon()->AddMaxAmmo(Count);
		Destroy();
	}
}

