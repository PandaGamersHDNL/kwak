// Copyright Epic Games, Inc. All Rights Reserved.

#include "kwakGameMode.h"
#include "kwakHUD.h"
#include "kwakCharacter.h"
#include "UObject/ConstructorHelpers.h"

AkwakGameMode::AkwakGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AkwakHUD::StaticClass();
}
