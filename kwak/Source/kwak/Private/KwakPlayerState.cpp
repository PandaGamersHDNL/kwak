// Fill out your copyright notice in the Description page of Project Settings.


#include "KwakPlayerState.h"

void AKwakPlayerState::OnRep_Score() {
    // on score change call the hud to update the AOD scoreboard if need
  //(Cast<APlayerController>(GetInstigatorController()))->GetHUD()->UpdateScore();
  UE_LOG(LogTemp, Warning, TEXT("shooting distance %i"), GetScore());

  if (GEngine)
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
            FString::Printf(TEXT("World delta for current frame equals %f"),
                            GetScore()));
}

void AKwakPlayerState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty> &OutLifetimeProps) const {
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);
  DOREPLIFETIME(AKwakPlayerState, Deaths);
}
