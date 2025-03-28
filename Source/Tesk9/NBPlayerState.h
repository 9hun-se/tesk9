
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NBPlayerState.generated.h"


UCLASS()
class TESK9_API ANBPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ANBPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	//플레이어+번호
	UPROPERTY(Replicated)
	FString PlayerNameString;
	//현재 시도 횟수
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 LostChance;
	//최대 시도 횟수
	UPROPERTY(Replicated)
	int32 MaxChance;
	
	FString GetPlayerInfoString();
};
