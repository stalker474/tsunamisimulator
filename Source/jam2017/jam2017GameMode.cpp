// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "jam2017.h"
#include "jam2017GameMode.h"
#include "jam2017PlayerController.h"
#include "jam2017Character.h"

Ajam2017GameMode::Ajam2017GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Ajam2017PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}