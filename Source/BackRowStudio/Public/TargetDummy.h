#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "TargetDummy.generated.h"

UCLASS()
class BACKROWSTUDIO_API ATargetDummy : public ADamageActor
{
    GENERATED_BODY()
    ATargetDummy();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float) override;

    virtual void TakeDamage(int, AActor *) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target Dummy")
    class UTextRenderComponent *Text;
};
