#include "ReplicationLabGameMode.h"

#include "ReplicationLabArena.h"
#include "ReplicationLabCharacter.h"
#include "ReplicationLabEnergyNode.h"
#include "ReplicationLabHUD.h"
#include "ReplicationLab.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

AReplicationLabGameMode::AReplicationLabGameMode()
{
    DefaultPawnClass = AReplicationLabCharacter::StaticClass();
    HUDClass = AReplicationLabHUD::StaticClass();
}

void AReplicationLabGameMode::BeginPlay()
{
    Super::BeginPlay();

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AReplicationLabArena* Arena = GetWorld()->SpawnActor<AReplicationLabArena>(AReplicationLabArena::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
    AReplicationLabEnergyNode* EnergyNode = GetWorld()->SpawnActor<AReplicationLabEnergyNode>(AReplicationLabEnergyNode::StaticClass(), FVector(250.0f, 0.0f, 130.0f), FRotator::ZeroRotator, SpawnParameters);

    UE_LOG(LogReplicationLab, Log, TEXT("Replication Lab initialized. Arena=%s EnergyNode=%s NetMode=%d"), *GetNameSafe(Arena), *GetNameSafe(EnergyNode), static_cast<int32>(GetNetMode()));

    if (EnergyNode != nullptr && FParse::Param(FCommandLine::Get(), TEXT("ReplicationLabSelfTest")))
    {
        EnergyNode->ToggleCharge(this);
        UE_LOG(LogReplicationLab, Log, TEXT("Self-test toggled the authority-owned Energy Node."));
    }
}

void AReplicationLabGameMode::RestartPlayer(AController* NewPlayer)
{
    if (NewPlayer == nullptr || DefaultPawnClass == nullptr)
    {
        return;
    }

    if (APawn* ExistingPawn = NewPlayer->GetPawn())
    {
        NewPlayer->UnPossess();
        ExistingPawn->Destroy();
    }

    const int32 PlayerId = NewPlayer->PlayerState != nullptr ? NewPlayer->PlayerState->GetPlayerId() : 0;
    const float SideOffset = (PlayerId % 2 == 0) ? -280.0f : 280.0f;
    const FTransform SpawnTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(-500.0f, SideOffset, 120.0f));

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = NewPlayer;
    SpawnParameters.Instigator = NewPlayer->GetPawn();
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    if (APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnTransform, SpawnParameters))
    {
        NewPlayer->Possess(NewPawn);
    }
}

