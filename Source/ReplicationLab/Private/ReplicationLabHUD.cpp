#include "ReplicationLabHUD.h"

#include "ReplicationLabCharacter.h"
#include "ReplicationLabEnergyNode.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"

namespace
{
    const TCHAR* ToDisplayString(ENetMode NetMode)
    {
        switch (NetMode)
        {
        case NM_Client:
            return TEXT("Client");
        case NM_ListenServer:
            return TEXT("Listen Server");
        case NM_DedicatedServer:
            return TEXT("Dedicated Server");
        case NM_Standalone:
        default:
            return TEXT("Standalone");
        }
    }

    const TCHAR* ToDisplayString(ENetRole NetRole)
    {
        switch (NetRole)
        {
        case ROLE_Authority:
            return TEXT("Authority");
        case ROLE_AutonomousProxy:
            return TEXT("Autonomous Proxy");
        case ROLE_SimulatedProxy:
            return TEXT("Simulated Proxy");
        case ROLE_None:
        default:
            return TEXT("None");
        }
    }
}

void AReplicationLabHUD::DrawHUD()
{
    Super::DrawHUD();

    if (Canvas == nullptr || GetWorld() == nullptr || GEngine == nullptr)
    {
        return;
    }

    const AReplicationLabCharacter* Character = Cast<AReplicationLabCharacter>(GetOwningPawn());
    AReplicationLabEnergyNode* EnergyNode = nullptr;
    for (TActorIterator<AReplicationLabEnergyNode> It(GetWorld()); It; ++It)
    {
        EnergyNode = *It;
        break;
    }

    const FString NetMode = ToDisplayString(GetWorld()->GetNetMode());
    const FString LocalRole = Character != nullptr ? ToDisplayString(Character->GetLocalRole()) : TEXT("No Pawn");
    const FString Charge = EnergyNode != nullptr
        ? FString::Printf(TEXT("Energy Node: %.0f%% | Activations: %d"), EnergyNode->GetChargePercent(), EnergyNode->GetActivationCount())
        : TEXT("Energy Node: waiting for server");

    const TArray<FString> Lines =
    {
        TEXT("MULTIPLAYER INTERACTION LAB"),
        FString::Printf(TEXT("Net mode: %s"), *NetMode),
        FString::Printf(TEXT("Local role: %s"), *LocalRole),
        Charge,
        TEXT("Aim at the node and press E. Server authority toggles the replicated state.")
    };

    float VerticalOffset = 36.0f;
    for (const FString& Line : Lines)
    {
        FCanvasTextItem TextItem(FVector2D(36.0f, VerticalOffset), FText::FromString(Line), GEngine->GetSmallFont(), FLinearColor::White);
        TextItem.EnableShadow(FLinearColor::Black);
        Canvas->DrawItem(TextItem);
        VerticalOffset += 24.0f;
    }
}

