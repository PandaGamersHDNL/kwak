// Copyright Epic Games, Inc. All Rights Reserved.

#include "kwakGameModeBase.h"
#include "KwakCharacter.h"

void AkwakGameModeBase::OnPlayerKilled(AKwakCharacter *PlayerPawn)
{
    auto controller = PlayerPawn->GetController();
    controller->UnPossess();
    RestartPlayerAtPlayerStart(controller, ChoosePlayerStart(controller));
}
