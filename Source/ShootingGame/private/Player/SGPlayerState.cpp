#include "SGPlayerState.h"
#include "SGPlayer.h"

void ASGPlayerState::InitPlayerData(ASGPlayer* Player)
{
	SGCHECK(Player);

	int32 Health = Player->GetHealth();
	MaxHP = Health;
	CurrentHP = Health;
}

void ASGPlayerState::SetHPToDamage(int32 Damage)
{
	SetHP(FMath::Clamp(CurrentHP - Damage, 0, MaxHP));

	SGLOG(Warning, TEXT("Current HP : %d"), CurrentHP);
}

void ASGPlayerState::SetHP(int32 NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP <= 0)
	{
		OnHPIsZero.Broadcast();
	}
}

float ASGPlayerState::GetHPRatio() const
{
	float HPRatio = static_cast<float>(CurrentHP) / static_cast<float>(MaxHP);
	return HPRatio;
}

bool ASGPlayerState::IsMaxHP() const
{
	if (CurrentHP == MaxHP)
	{
		return true;
	}
	return false;
}

void ASGPlayerState::HealHP()
{
	SetHP(FMath::Clamp(CurrentHP + 1, 0, MaxHP));
}
