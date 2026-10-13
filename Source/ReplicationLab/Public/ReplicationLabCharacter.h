#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplicationLabCharacter.generated.h"

class AReplicationLabEnergyNode;

UCLASS()
class REPLICATIONLAB_API AReplicationLabCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AReplicationLabCharacter();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Interact();
    AReplicationLabEnergyNode* FindInteractionTarget() const;

    UFUNCTION(Server, Reliable)
    void ServerInteract(AReplicationLabEnergyNode* EnergyNode);
};

