// Fill out your copyright notice in the Description page of Project Settings.

#include "KwakCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "KwakPlayerState.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "kwakGameModeBase.h"
#include "kwakGameState.h"

// #include "NiagaraSystem.h"

// Sets default values
AKwakCharacter::AKwakCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = false;
    // Create a CameraComponent
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 0)); // Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    /* ConstructorHelpers::FObjectFinder<UNiagaraSystem> guntrailObject(
        TEXT("NiagaraSystem'/Game/GunTrail_NS.GunTrail_NS'"));
    if (guntrailObject.Succeeded()) {
    GunTrailSystem = guntrailObject.Object;
    } else {
      UE_LOG(LogTemp, Warning, TEXT("could not create gun trail system"));
    }*/
}

// set relication
void AKwakCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AKwakCharacter, StartShot);
    DOREPLIFETIME(AKwakCharacter, EndShot);
    DOREPLIFETIME(AKwakCharacter, ShootDistance);
    // DOREPLIFETIME(AKwakCharacter, GunTrailSystem);
}

// Called when the game starts or when spawned
void AKwakCharacter::BeginPlay()
{
    Super::BeginPlay();
    // UE_LOG(LogTemp, Warning, TEXT("shooting distance %i"), ShootDistance);
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

    // movement
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAxis("MoveForward", this, &AKwakCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKwakCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    // actions
    PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AKwakCharacter::Shoot);
    // dash/ leap?
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

void AKwakCharacter::Shoot_Implementation()
{
    ShootOnServer();
}

void AKwakCharacter::ShootOnServer_Implementation()
{
    this->StartShot = GetActorLocation();
    this->EndShot = this->StartShot + (GetControlRotation().Vector() * ShootDistance);
    FHitResult hit;
    FCollisionQueryParams LinetraceParams;
    LinetraceParams.AddIgnoredActor(this);
    if (GetWorld()->LineTraceSingleByChannel(hit, StartShot, EndShot, ECollisionChannel::ECC_Visibility,
                                             LinetraceParams))
    {
        EndShot = hit.ImpactPoint;
        UE_LOG(LogTemp, Warning, TEXT("%s"), *hit.Actor->GetName());

        auto character = Cast<AKwakCharacter>(hit.Actor);
        if (character)
        {
            auto state = APawn::GetPlayerState();
            state->SetScore(state->GetScore() + 1);
            character->KillSelf();
            auto gamemodeBase = GetWorld()->GetAuthGameMode();
            if (gamemodeBase)
            {
                auto gamemode = Cast<AkwakGameModeBase>(gamemodeBase);
                if (gamemode->WinKills <= state->GetScore())
                {
                    gamemode->EndMatch();
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("not server for gamemode"));
            }
        }
    }
    // UE_LOG(LogTemp, Warning, TEXT("Shoot trail"));
    ShootTrails();
}

// guntrailsystem not defined Temp fix -> bp
/* void AKwakCharacter::ShootTrails_Implementation() {

    if (GunTrailSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("No gun trail system set"));
        return;
    }
    auto system = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GunTrailSystem, StartShot, FRotator(),
                                                                 FVector(), true, true, ENCPoolMethod::None, true);
    system->SetVectorParameter("beamEnd", EndShot);
}*/

void AKwakCharacter::KillSelf_Implementation()
{
    // TODO
    Cast<AKwakPlayerState>(GetPlayerState())->Deaths++;
    UE_LOG(LogTemp, Warning, TEXT("kill self"));
    // set the client's camera (client)
    KillHitbox();

    // do after x seconds
    auto gamemode = Cast<AkwakGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    gamemode->OnPlayerKilled(this);
    // this->Destroy(); //TODO add this after delay is added
}

void AKwakCharacter::KillHitbox_Implementation()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}
