#include "TargetDummy.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATargetDummy::ATargetDummy()
{
    Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
    Text->SetupAttachment(GetRootComponent());
    Text->SetText(FText::FromString("Damage Taken: 0.0"));
    Text->SetHorizontalAlignment(EHTA_Center);
    Text->SetWorldSize(50.0f);
    Text->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    PrimaryActorTick.bCanEverTick = true;
}

void ATargetDummy::BeginPlay() { Super::BeginPlay(); }

void ATargetDummy::Tick(float x)
{
    Super::Tick(x);

    if (const APlayerCameraManager *playerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager)
    {
        auto vector = playerCamera->GetCameraLocation() - GetActorLocation();
        vector.Normalize();
        Text->SetRelativeRotation(UKismetMathLibrary::MakeRotFromX(vector));
    }
}

void ATargetDummy::TakeDamage(int damage, AActor *actor) { Text->SetText(FText::FromString("Damage Taken: " + FString::SanitizeFloat(damage / 100.f))); }
