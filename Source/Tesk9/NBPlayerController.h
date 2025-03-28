#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NBPlayerState.h"
#include "NBPlayerController.generated.h"


class UNBChatInput;
class UUserWidget;

UCLASS()
class TESK9_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ANBPlayerController();
	virtual void BeginPlay() override;
	//채팅 메시지 설정(관리)
	void SetChatMessageString(const FString& InChatMessageString);

	//채팅 메시지 출력
	void PrintChatMessageString(const FString& InChatMessageString);

	//멀티플레이 채팅
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	//채팅 위젯 연결 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBChatInput> ChatInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UNBChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;

	//공지 위젯 연결
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText TextBlock_Chance;
};
