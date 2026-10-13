#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicationLabArena.generated.h"

class UStaticMeshComponent;

UCLASS()
class REPLICATIONLAB_API AReplicationLabArena : public AActor
{
    GENERATED_BODY()

public:
    AReplicationLabArena();

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> FloorMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BackWallMesh;
};

