#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NBGameModeBase.generated.h"

class ANBPlayerController;

UCLASS()
class TESK9_API ANBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	//���� ����
	UFUNCTION(BlueprintCallable)
	FString GenerateRandomNumber();

	bool IsGuessNumberString(const FString& InNumberString);
	//��� ����
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;

	void PrintChatMessageString(ANBPlayerController* InChattingPlayerController, const FString& InChatMessageString);
	//�õ� Ƚ�� ����
	void IncreaseChance(ANBPlayerController* InChattingPlayerController);
	//���� �ʱ�ȭ
	void ResetGame();
	//���� ����
	void JudgeGame(ANBPlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	//���� ����
	FString SecretNumberString;
	//��ü �÷��̾� �迭
	TArray<TObjectPtr<ANBPlayerController>> ArrayOfPlayerControllers;


};
