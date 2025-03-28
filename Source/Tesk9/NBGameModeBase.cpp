#include "NBGameModeBase.h"
#include "NBGameStateBase.h"
#include <random>
#include "NBPlayerController.h"
#include "EngineUtils.h"
#include "NBPlayerState.h"


void ANBGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	
	ANBPlayerController* NBPlayerController = Cast<ANBPlayerController>(NewPlayer);
	if (IsValid(NBPlayerController) == true)
	{
		ArrayOfPlayerControllers.Add(NBPlayerController);
		//전체 플레이어 배열에 새플레이어 추가+넘버링
		ANBPlayerState* NBPS = NBPlayerController->GetPlayerState<ANBPlayerState>();
		//공지위젯 출력
		NBPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));

		if (IsValid(NBPS) == true)
		{
			NBPS->PlayerNameString = TEXT("Player") + FString::FromInt(ArrayOfPlayerControllers.Num());
		}

		ANBGameStateBase* NBGameStateBase = GetGameState<ANBGameStateBase>();
		if (IsValid(NBGameStateBase) == true)
		{
			NBGameStateBase->MulticastRPCBroadcastLoginMessage(NBPS->PlayerNameString);
		}
	}
}

FString ANBGameModeBase::GenerateRandomNumber()
{
	TSet<int32> Numbers;
	while (Numbers.Num() < 3)
	{
		int32 i = FMath::RandRange(1, 9);
		Numbers.Add(i);
	}
	//반환 결과
	FString Result;
	//생성된 숫자
	int32 Gnum = 0;
	if (Numbers.Num() == 3)
	{
		TArray<int32> NumberArray = Numbers.Array();
		for (int32 k = 0; k < 3; k++) 
		{
			Result += FString::Printf(TEXT("%d"), NumberArray[k]);
		}
		Gnum = NumberArray[0] * 100 + NumberArray[1] * 10 + NumberArray[2];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("세 개의 고유한 숫자를 생성하지 못했습니다."));
	}

	
	UE_LOG(LogTemp, Log, TEXT("생성된 세 자리 숫자:%d"),Gnum);

	return Result;
}
//세자리수인지 판별
bool ANBGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {

		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;

	} while (false);

	return bCanPlay;
}
//결과 판정
FString ANBGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void ANBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateRandomNumber();
}

void ANBGameModeBase::PrintChatMessageString(ANBPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString ChatMessageString = InChatMessageString;
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		IncreaseChance(InChattingPlayerController);
		for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
		{
			ANBPlayerController* NBPlayerController = *It;
			if (IsValid(NBPlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				NBPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
		{
			ANBPlayerController* NBPlayerController = *It;
			if (IsValid(NBPlayerController) == true)
			{
				NBPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}
//사용한 도전 횟수
void ANBGameModeBase::IncreaseChance(ANBPlayerController* InChattingPlayerController)
{
	ANBPlayerState* NBPS = InChattingPlayerController->GetPlayerState<ANBPlayerState>();
	if (IsValid(NBPS) == true)
	{
		NBPS->LostChance++;
	}
}
//게임 초기화
void ANBGameModeBase::ResetGame()
{
	SecretNumberString = GenerateRandomNumber();

	for (const auto& NBPlayerController : ArrayOfPlayerControllers)
	{
		ANBPlayerState* NBPS = NBPlayerController->GetPlayerState<ANBPlayerState>();
		if (IsValid(NBPS) == true)
		{
			NBPS->LostChance = 0;
		}
	}
}

void ANBGameModeBase::JudgeGame(ANBPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		ANBPlayerState* NBPS = InChattingPlayerController->GetPlayerState<ANBPlayerState>();
		for (const auto& NBPlayerController : ArrayOfPlayerControllers)
		{
			if (IsValid(NBPS) == true)
			{
				FString CombinedMessageString = NBPS->PlayerNameString + TEXT(" has won the game.");
				NBPlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& NBPlayerController : ArrayOfPlayerControllers)
		{
			ANBPlayerState* NBPS = NBPlayerController->GetPlayerState<ANBPlayerState>();
			if (IsValid(NBPS) == true)
			{
				if (NBPS->LostChance < NBPS->MaxChance)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& NBPlayerController : ArrayOfPlayerControllers)
			{
				NBPlayerController->NotificationText = FText::FromString(TEXT("Draw..."));

				ResetGame();
			}
		}
	}
}