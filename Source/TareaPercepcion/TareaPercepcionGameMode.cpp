// Copyright Epic Games, Inc. All Rights Reserved.

#include "TareaPercepcionGameMode.h"
#include "TareaPercepcionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATareaPercepcionGameMode::ATareaPercepcionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
