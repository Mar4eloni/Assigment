// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssigmentGameMode.h"
#include "AssigmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssigmentGameMode::AAssigmentGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
