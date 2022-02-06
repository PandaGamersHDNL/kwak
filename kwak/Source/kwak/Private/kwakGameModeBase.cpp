// Copyright Epic Games, Inc. All Rights Reserved.

#include "kwakGameModeBase.h"
#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/PendingNetGame.h"
#include "KwakCharacter.h"

void AkwakGameModeBase::OnPlayerKilled(AKwakCharacter *PlayerPawn)
{
    auto controller = PlayerPawn->GetController();
    controller->UnPossess();
    RestartPlayerAtPlayerStart(controller, ChoosePlayerStart(controller));
}

void AkwakGameModeBase::HandleMatchHasEnded()
{
    LoadLobby();
}

void AkwakGameModeBase::HandleMatchIsWaitingToStart()
{
    GetWorldSettings()->NotifyBeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("handle match is waiting to start %s"), (HasMatchStarted() ? "true" : "false"));
}

bool AkwakGameModeBase::ReadyToStartMatch_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ready to start match"));
    return playersReady;
}

void AkwakGameModeBase::StartMatch()
{
    //TODO create count down with visible UI
    SetMatchState(MatchState::InProgress); }
