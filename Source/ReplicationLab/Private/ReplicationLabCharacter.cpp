#include "ReplicationLabCharacter.h"

#include "ReplicationLabEnergyNode.h"
#include "ReplicationLab.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

AReplicationLabCharacter::AReplicationLabCharacter()
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void AReplicationLabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AReplicationLabCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AReplicationLabCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AReplicationLabCharacter::Interact);
}

void AReplicationLabCharacter::MoveForward(float Value)
{
    if (Controller != nullptr && !FMath::IsNearlyZero(Value))
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
        AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
    }
}

void AReplicationLabCharacter::MoveRight(float Value)
{
    if (Controller != nullptr && !FMath::IsNearlyZero(Value))
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
        AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
    }
}

void AReplicationLabCharacter::Interact()
{
    if (!IsLocallyControlled())
    {
        return;
    }

    if (AReplicationLabEnergyNode* Target = FindInteractionTarget())
    {
        ServerInteract(Target);
    }
}

AReplicationLabEnergyNode* AReplicationLabCharacter::FindInteractionTarget() const
{
    if (Controller == nullptr)
    {
        return nullptr;
    }

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    FHitResult Hit;
    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ReplicationLabInteraction), false, this);
    const FVector TraceEnd = ViewLocation + (ViewRotation.Vector() * 350.0f);

    if (GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, TraceEnd, ECC_Visibility, QueryParams))
    {
        return Cast<AReplicationLabEnergyNode>(Hit.GetActor());
    }

    return nullptr;
}

void AReplicationLabCharacter::ServerInteract_Implementation(AReplicationLabEnergyNode* EnergyNode)
{
    if (EnergyNode == nullptr || !EnergyNode->CanBeInteractedWithBy(this))
    {
        return;
    }

    EnergyNode->ToggleCharge(this);
    UE_LOG(LogReplicationLab, Log, TEXT("Server accepted interaction from %s."), *GetName());
}

