// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "KwakPlayerState.generated.h"

/**
 *
 */
UCLASS()
class KWAK_API AKwakPlayerState : public APlayerState
{
    GENERATED_BODY()

  public:
    virtual void OnRep_Score() override;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int Deaths = 0;

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const;
};
