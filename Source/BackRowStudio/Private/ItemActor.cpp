#include "ItemActor.h"
#include "Components/SphereComponent.h"
#include "InventoryItemAsset.h"

AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SphereCollider->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
    SphereCollider->InitSphereRadius(400.f);

    Item = nullptr;
}

void AItemActor::BeginPlay() { Super::BeginPlay(); }

void AItemActor::Tick(float delta_time) { Super::Tick(delta_time); }
