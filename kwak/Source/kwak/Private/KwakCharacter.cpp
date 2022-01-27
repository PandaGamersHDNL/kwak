// Fill out your copyright notice in the Description page of Project Settings.

#include "KwakCharacter.h"

// Sets default values
AKwakCharacter::AKwakCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKwakCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AKwakCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AKwakCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // Bind movement events
    PlayerInputComponent->BindAxis("MoveForward", this, &AKwakCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKwakCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AKwakCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AKwakCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorRightVector(), Value);
    }
}
