#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ReplicationLabHUD.generated.h"

UCLASS()
class REPLICATIONLAB_API AReplicationLabHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};

