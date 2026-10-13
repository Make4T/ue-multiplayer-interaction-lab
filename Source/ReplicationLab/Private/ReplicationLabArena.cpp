#include "ReplicationLabArena.h"

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
}

