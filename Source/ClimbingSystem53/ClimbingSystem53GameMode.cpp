// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClimbingSystem53GameMode.h"
#include "ClimbingSystem53Character.h"
#include "UObject/ConstructorHelpers.h"

AClimbingSystem53GameMode::AClimbingSystem53GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
