// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShintoGameMode.h"
#include "ShintoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShintoGameMode::AShintoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
