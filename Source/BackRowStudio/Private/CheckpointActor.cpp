#include "CheckpointActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"
#include "ItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Wolf.h"
#include "WolfAIController.h"

ACheckpointActor::ACheckpointActor()
{
    PrimaryActorTick.bCanEverTick = false;

    CheckpointCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointCollisionBox"));
    CheckpointCollisionBox->InitBoxExtent(FVector(100));
    CheckpointCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CheckpointCollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    CheckpointCollisionBox->SetupAttachment(GetRootComponent());

    SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
    SpawnPoint->SetupAttachment(CheckpointCollisionBox);
    SpawnPoint->SetRelativeScale3D(FVector(0.1));
    SpawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SpawnPoint->SetCollisionResponseToAllChannels(ECR_Ignore);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SpawnPointMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    SpawnPoint->SetStaticMesh(SpawnPointMesh.Object);
    static ConstructorHelpers::FObjectFinder<UMaterial> SpawnPointMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
    SpawnPoint->SetMaterial(0, SpawnPointMaterial.Object);
    SpawnPoint->SetHiddenInGame(true);

    SpawnPointArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointArrow"));
    SpawnPointArrow->SetupAttachment(SpawnPoint);
    SpawnPointArrow->ArrowSize = 4;
    SpawnPointArrow->ArrowLength = 100;
}

void ACheckpointActor::BeginPlay()
{
    Super::BeginPlay();

    CheckpointCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int other_index, bool from_sweep, const FHitResult &sweep_result)
{
    if (const auto character = Cast<AMainCharacter>(other_actor); character && !IsTriggered)
    {
        FHitResult hitResult;
        GetWorld()->SweepSingleByChannel(hitResult, GetActorLocation(), GetActorLocation() - FVector(0, 0, 1000), FQuat::Identity, ECC_Pawn, FCollisionShape::MakeBox(FVector(5)));
        SavedData.PlayerLocationOffset = (character->GetActorLocation() - hitResult.ImpactPoint) * FVector(0, 0, 1);

        for (auto item : character->MyInv->Items)
        {
            SavedData.Items.Add(item);
        }
        for (auto spell : character->MyInv->Spells)
        {
            SavedData.Spells.Add(spell);
        }
        SavedData.Health = character->Health;

        TArray<AActor *> foundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolf::StaticClass(), foundActors);

        for (const auto actor : foundActors)
        {
            if (const auto wolf = Cast<AWolf>(actor); wolf->WolfAIController->CanMove)
            {
                SavedData.EnemyLocations.Add(wolf->GetUniqueID(), wolf->GetActorLocation());
            }
        }

        foundActors.Empty();

        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemActor::StaticClass(), foundActors);

        for (const auto actor : foundActors)
        {
            SavedData.ItemsInWorld.Add(actor->GetUniqueID(), !Cast<AItemActor>(actor)->IsPickedUp);
        }

        character->SetCheckpoint(this);
        IsTriggered = true;
    }
}

void ACheckpointActor::RespawnOthers()
{
    TArray<AActor *> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolf::StaticClass(), foundActors);

    TMap<uint32, AWolf *> mappedWolfs;

    for (AActor *actor : foundActors)
    {
        mappedWolfs.Add(actor->GetUniqueID(), Cast<AWolf>(actor));
    }

    foundActors.Empty();

    for (auto enemy : SavedData.EnemyLocations)
    {
        mappedWolfs[enemy.Key]->SetActorLocation(enemy.Value);
        mappedWolfs[enemy.Key]->GetMesh()->SetVisibility(true);
        mappedWolfs[enemy.Key]->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        mappedWolfs[enemy.Key]->AttackHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemActor::StaticClass(), foundActors);
    TMap<uint32, AItemActor *> mappedItems;
    for (AActor *actor : foundActors)
    {
        mappedItems.Add(actor->GetUniqueID(), Cast<AItemActor>(actor));
    }

    for (const auto items : SavedData.ItemsInWorld)
    {
        if (items.Value)
        {
            const auto item = mappedItems[items.Key];
            item->IsPickedUp = false;
            item->Mesh->SetVisibility(true);
            item->SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        }
    }
}

void ACheckpointActor::RespawnPlayer(AMainCharacter *player)
{
    FHitResult hitResult;
    GetWorld()->SweepSingleByChannel(hitResult, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentLocation() - FVector(0, 0, 10000), FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeBox(FVector(5)));
    auto loc = hitResult.Location - FVector(0, 0, 5) + SavedData.PlayerLocationOffset;
    player->SetActorLocation(loc);
    auto controller = player->GetController();
    auto rot = controller->GetControlRotation();
    controller->ClientSetRotation(FRotator(rot.Pitch, SpawnPoint->GetComponentRotation().Yaw, 0));
    player->MyInv->Items = SavedData.Items;
    player->MyInv->Spells = SavedData.Spells;
    player->Health = SavedData.Health;
    TArray<AActor *> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolf::StaticClass(), foundActors);
    for (AActor *foundActor : foundActors)
    {
        Cast<AWolf>(foundActor)->WolfAIController->CanMove = true;
    }
}
