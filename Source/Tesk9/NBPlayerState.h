
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
	//�÷��̾�+��ȣ
	UPROPERTY(Replicated)
	FString PlayerNameString;
	//���� �õ� Ƚ��
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 LostChance;
	//�ִ� �õ� Ƚ��
	UPROPERTY(Replicated)
	int32 MaxChance;
	
	FString GetPlayerInfoString();
};
