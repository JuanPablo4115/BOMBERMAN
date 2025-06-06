// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject6GameMode.h"
#include "MyProject6PlayerController.h"
#include "MyProject6Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject6GameMode::AMyProject6GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyProject6PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}