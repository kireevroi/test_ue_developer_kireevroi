// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_FntasticGameMode.h"
#include "UE_FntasticCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_FntasticGameMode::AUE_FntasticGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
