// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "kwakGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class KWAK_API AkwakGameModeBase : public AGameMode
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    void OnPlayerKilled(class AKwakCharacter *PlayerPawn);

    UFUNCTION()
    virtual void HandleMatchHasEnded() override;

    UPROPERTY()
    int WinKills = 20;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool playersReady = false;

    UFUNCTION(BlueprintImplementableEvent)
        void LoadLobby();
    
    virtual void HandleMatchIsWaitingToStart() override;

    // Override Implementation of ReadyToStartMatch
    virtual bool ReadyToStartMatch_Implementation() override;

    virtual void StartMatch() override;
};
