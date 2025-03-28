
#include "NBPawn.h"
#include "Tesk9.h"



void ANBPawn::BeginPlay()
{
	Super::BeginPlay();
	FString NetModeString = Tesk9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("NBPawn::BeginPlay() %s [%s]"), *Tesk9FunctionLibrary::GetNetModeString(this), *NetModeString);
	Tesk9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}


void ANBPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetModeString = Tesk9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *Tesk9FunctionLibrary::GetNetModeString(this), *NetModeString);
	Tesk9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}