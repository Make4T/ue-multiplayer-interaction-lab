#include "ReplicationLabEnergyNode.h"

#include "ReplicationLab.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

AReplicationLabEnergyNode::AReplicationLabEnergyNode()
{
    bReplicates = true;
    bAlwaysRelevant = true;
    SetReplicateMovement(false);

    NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
    RootComponent = NodeMesh;
    NodeMesh->SetCollisionProfileName(TEXT("BlockAll"));
    NodeMesh->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.8f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        NodeMesh->SetStaticMesh(CubeMesh.Object);
    }

    StatusLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("StatusLight"));
    StatusLight->SetupAttachment(NodeMesh);
    StatusLight->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
    StatusLight->SetIntensity(3500.0f);
    StatusLight->SetAttenuationRadius(500.0f);

    Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
    Label->SetupAttachment(NodeMesh);
    Label->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
    Label->SetHorizontalAlignment(EHTA_Center);
    Label->SetTextRenderColor(FColor::White);
    Label->SetWorldSize(34.0f);
}

void AReplicationLabEnergyNode::BeginPlay()
{
    Super::BeginPlay();
    ApplyChargeVisuals();
}

bool AReplicationLabEnergyNode::CanBeInteractedWithBy(const AActor* Interactor) const
{
    return HasAuthority() && Interactor != nullptr && FVector::DistSquared(Interactor->GetActorLocation(), GetActorLocation()) <= FMath::Square(350.0f);
}

void AReplicationLabEnergyNode::ToggleCharge(const AActor* Interactor)
{
    check(HasAuthority());

    ChargePercent = ChargePercent > 0.0f ? 0.0f : 100.0f;
    ++ActivationCount;
    ApplyChargeVisuals();
    ForceNetUpdate();

    UE_LOG(LogReplicationLab, Log, TEXT("Energy Node changed by %s. Charge=%.0f Activations=%d"), *GetNameSafe(Interactor), ChargePercent, ActivationCount);
}

void AReplicationLabEnergyNode::OnRep_ChargeState()
{
    ApplyChargeVisuals();
    UE_LOG(LogReplicationLab, Log, TEXT("Energy Node replicated to client. Charge=%.0f Activations=%d"), ChargePercent, ActivationCount);
}

void AReplicationLabEnergyNode::ApplyChargeVisuals()
{
    const bool bIsCharged = ChargePercent > 0.0f;
    StatusLight->SetLightColor(bIsCharged ? FLinearColor(0.05f, 1.0f, 0.35f) : FLinearColor(1.0f, 0.08f, 0.03f));
    NodeMesh->SetRelativeScale3D(bIsCharged ? FVector(1.2f, 1.2f, 2.3f) : FVector(1.2f, 1.2f, 1.8f));
    Label->SetText(FText::FromString(FString::Printf(TEXT("ENERGY NODE\n%s\nActivations: %d"), bIsCharged ? TEXT("CHARGED") : TEXT("OFFLINE"), ActivationCount)));
}

void AReplicationLabEnergyNode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AReplicationLabEnergyNode, ChargePercent);
    DOREPLIFETIME(AReplicationLabEnergyNode, ActivationCount);
}

