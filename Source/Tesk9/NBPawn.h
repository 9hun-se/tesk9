﻿
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NBPawn.generated.h"

UCLASS()
class TESK9_API ANBPawn : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

};
