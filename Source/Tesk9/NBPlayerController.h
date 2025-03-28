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
	//ä�� �޽��� ����(����)
	void SetChatMessageString(const FString& InChatMessageString);

	//ä�� �޽��� ���
	void PrintChatMessageString(const FString& InChatMessageString);

	//��Ƽ�÷��� ä��
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	//ä�� ���� ���� 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBChatInput> ChatInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UNBChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;

	//���� ���� ����
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
