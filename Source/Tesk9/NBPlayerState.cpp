
#include "NBPlayerState.h"
#include "Net/UnrealNetwork.h"


ANBPlayerState::ANBPlayerState()
	: PlayerNameString(TEXT("None"))
	,LostChance(0)
	,MaxChance(3)
{
	bReplicates = true;
}

void ANBPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, LostChance);
	DOREPLIFETIME(ThisClass, MaxChance);
}
//���� �õ� Ƚ�� �߰��ؼ� ���ڿ�ȭ
FString ANBPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(LostChance) + TEXT("/") + FString::FromInt(MaxChance) + TEXT(")");
	return PlayerInfoString;
}