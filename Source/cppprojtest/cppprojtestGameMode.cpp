// Copyright Epic Games, Inc. All Rights Reserved.

#include "cppprojtestGameMode.h"
#include "cppprojtestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcppprojtestGameMode::AcppprojtestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
