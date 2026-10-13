#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicationLabArena.generated.h"

class UStaticMeshComponent;
class UDirectionalLightComponent;
class UPointLightComponent;
class USkyLightComponent;

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

    // Runtime lighting keeps the lab readable on the otherwise unlit Entry map.
    UPROPERTY(VisibleAnywhere, Category = "Lighting")
    TObjectPtr<UDirectionalLightComponent> KeyLight;

    UPROPERTY(VisibleAnywhere, Category = "Lighting")
    TObjectPtr<USkyLightComponent> SkyLight;

    UPROPERTY(VisibleAnywhere, Category = "Lighting")
    TObjectPtr<UPointLightComponent> FillLight;
};

