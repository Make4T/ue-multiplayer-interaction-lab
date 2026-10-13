#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicationLabEnergyNode.generated.h"

class UPointLightComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class REPLICATIONLAB_API AReplicationLabEnergyNode : public AActor
{
    GENERATED_BODY()

public:
    AReplicationLabEnergyNode();

    bool CanBeInteractedWithBy(const AActor* Interactor) const;
    void ToggleCharge(const AActor* Interactor);
    float GetChargePercent() const { return ChargePercent; }
    int32 GetActivationCount() const { return ActivationCount; }

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UFUNCTION()
    void OnRep_ChargeState();

    void ApplyChargeVisuals();

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> NodeMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UPointLightComponent> StatusLight;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UTextRenderComponent> Label;

    UPROPERTY(ReplicatedUsing = OnRep_ChargeState, VisibleInstanceOnly, Category = "Replication")
    float ChargePercent = 0.0f;

    UPROPERTY(ReplicatedUsing = OnRep_ChargeState, VisibleInstanceOnly, Category = "Replication")
    int32 ActivationCount = 0;
};

