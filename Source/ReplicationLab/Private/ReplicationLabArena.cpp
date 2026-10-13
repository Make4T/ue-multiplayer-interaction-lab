#include "ReplicationLabArena.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AReplicationLabArena::AReplicationLabArena()
{
    bReplicates = true;
    bAlwaysRelevant = true;

    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
    RootComponent = FloorMesh;
    FloorMesh->SetCollisionProfileName(TEXT("BlockAll"));
    FloorMesh->SetRelativeScale3D(FVector(18.0f, 18.0f, 0.2f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        FloorMesh->SetStaticMesh(CubeMesh.Object);
    }

    BackWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWallMesh"));
    BackWallMesh->SetupAttachment(FloorMesh);
    BackWallMesh->SetCollisionProfileName(TEXT("BlockAll"));
    BackWallMesh->SetRelativeLocation(FVector(900.0f, 0.0f, 250.0f));
    BackWallMesh->SetRelativeScale3D(FVector(0.2f, 18.0f, 2.5f));
    if (CubeMesh.Succeeded())
    {
        BackWallMesh->SetStaticMesh(CubeMesh.Object);
    }

    KeyLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("KeyLight"));
    KeyLight->SetupAttachment(FloorMesh);
    KeyLight->SetMobility(EComponentMobility::Movable);
    KeyLight->SetRelativeRotation(FRotator(-52.0f, -35.0f, 0.0f));
    KeyLight->SetIntensity(12.0f);
    KeyLight->SetLightColor(FLinearColor(0.92f, 0.96f, 1.0f));
    KeyLight->SetCastShadows(true);

    SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
    SkyLight->SetupAttachment(FloorMesh);
    SkyLight->SetMobility(EComponentMobility::Movable);
    SkyLight->SetIntensity(1.4f);
    SkyLight->SetLightColor(FLinearColor(0.55f, 0.70f, 1.0f));
    SkyLight->SetRealTimeCaptureEnabled(true);

    FillLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FillLight"));
    FillLight->SetupAttachment(FloorMesh);
    FillLight->SetMobility(EComponentMobility::Movable);
    FillLight->SetRelativeLocation(FVector(-350.0f, -450.0f, 500.0f));
    FillLight->SetIntensity(7000.0f);
    FillLight->SetAttenuationRadius(2200.0f);
    FillLight->SetLightColor(FLinearColor(0.20f, 0.50f, 1.0f));
    FillLight->SetCastShadows(false);
}

