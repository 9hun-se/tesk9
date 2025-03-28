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

	//난수 생성
	UFUNCTION(BlueprintCallable)
	FString GenerateRandomNumber();

	bool IsGuessNumberString(const FString& InNumberString);
	//결과 판정
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;

	void PrintChatMessageString(ANBPlayerController* InChattingPlayerController, const FString& InChatMessageString);
	//시도 횟수 증가
	void IncreaseChance(ANBPlayerController* InChattingPlayerController);
	//게임 초기화
	void ResetGame();
	//승패 판정
	void JudgeGame(ANBPlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	//랜덤 난수
	FString SecretNumberString;
	//전체 플레이어 배열
	TArray<TObjectPtr<ANBPlayerController>> ArrayOfPlayerControllers;


};
