// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "KwakGameSession.generated.h"

/**
 * 
 */
UCLASS()
class KWAK_API AKwakGameSession : public AGameSession
{
  GENERATED_BODY()

  virtual bool HandleStartMatchRequest() override;
	
};
