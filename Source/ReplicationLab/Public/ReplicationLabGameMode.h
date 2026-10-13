#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReplicationLabGameMode.generated.h"

UCLASS()
class REPLICATIONLAB_API AReplicationLabGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AReplicationLabGameMode();

    virtual void BeginPlay() override;
    virtual void RestartPlayer(AController* NewPlayer) override;
};

