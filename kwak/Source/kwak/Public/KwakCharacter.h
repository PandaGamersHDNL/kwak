// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Net/UnrealNetwork.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
// has to be last
#include "KwakCharacter.generated.h"
class UCameraComponent;

UCLASS()
class KWAK_API AKwakCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    AKwakCharacter();

    UPROPERTY(Replicated, BlueprintReadOnly)
    FVector StartShot;

    UPROPERTY(Replicated, BlueprintReadOnly)
    FVector EndShot;

    UPROPERTY(Replicated, EditDefaultsOnly)
    int ShootDistance = 1000;

    UCameraComponent *FirstPersonCameraComponent;

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
    void MoveForward(float Value);
    void MoveRight(float Value);

    void KillSelf_Implementation();

    void KillHitbox_Implementation();

    UFUNCTION(Client, Reliable)
    void Shoot(); // first bp then cpp

    UFUNCTION(Server, Reliable)
    void ShootOnServer();

    /* UPROPERTY(EditDefaultsOnly, Replicated)
    class UNiagaraSystem* GunTrailSystem = nullptr;*/

    UFUNCTION(NetMulticast, Unreliable, BlueprintCallable)
    void ShootTrails();

    UFUNCTION(BlueprintImplementableEvent)
    void ShootTrails_Implementation();

    UFUNCTION(Server, Reliable)
    void KillSelf();

    UFUNCTION(NetMulticast, Reliable)
    void KillHitbox();
};
