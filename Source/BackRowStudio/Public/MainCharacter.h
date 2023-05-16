// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "MainCharacter.generated.h"

class UHealthBarWidget;
class UInventoryWidget;
class UMinimapWidget;
struct FInputActionValue;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECharacterAnimationState : uint8
{
    Idle = 0x00,
    Jumping = 0x01,
    Attack = 0x02,
    Pickup = 0x04,
    Death = 0x08,
    Attacked = 0x10
};

ENUM_CLASS_FLAGS(ECharacterAnimationState);

UCLASS()
class BACKROWSTUDIO_API AMainCharacter : public ACharacter, public IGenericTeamAgentInterface

{
    GENERATED_BODY()

    bool beingAttacked;

    float attackTimer;

    int attackingPower;

    float respawnTimer;

    void UnsetAnimationFlag(ECharacterAnimationState flag);

    bool CheckAnimationFlag(ECharacterAnimationState flag);

public:
    FGenericTeamId TeamID = FGenericTeamId(1);

    UPROPERTY(VisibleAnywhere, Category = "Animation State", meta = (Bitmask, BitmaskEnum = ECharacterAnimationState))
    uint8 AnimationState = 0;

    UPROPERTY(EditAnywhere, Category="Animation State")
    float AnimationAttackLength = 0.5f;

    UPROPERTY(VisibleAnywhere, Category="Animation State")
    float AnimationAttackTimer = 0.0f;

    UPROPERTY(EditAnywhere, Category="Animation State")
    float AnimationPickupLength = 0.5f;

    UPROPERTY(VisibleAnywhere, Category="Animation State")
    float AnimationPickupTimer = 0.0f;

    UPROPERTY(EditAnywhere, Category="Animation State")
    float AnimationAttackedLength = 0.5f;

    UPROPERTY(EditAnywhere, Category="Animation State")
    float AnimationAttackedTimer;

    UPROPERTY(EditAnywhere, Category = "Health")
    int Health = 1000;

    UPROPERTY(EditAnywhere, Category = "Health")
    int MaxHealth = 1000;

    UPROPERTY(EditAnywhere, Category = "Health")
    float AttackedTimeCooldown;

    bool OpenOrClosePause;

    AMainCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent *SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
    USpringArmComponent *MiniMapSpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
    USceneCaptureComponent2D *MinimapCam;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    class UInventoryComponent *MyInv;

    bool OpenInventory = true;

    bool CanOpenInventory = true;

    UPROPERTY()
    APlayerController *PC;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
    class ACheckpointActor *RespawnLocation;

#pragma region Widgets
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Minimap")
    TSubclassOf<UMinimapWidget> MiniMapWidgetTemplate;

    UPROPERTY(BlueprintReadOnly, Category = "Widget | Minimap")
    UMinimapWidget *MinimapWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Inventory")
    TSubclassOf<UInventoryWidget> MyInvWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Widget | Inventory")
    UInventoryWidget *InvWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Health")
    TSubclassOf<UHealthBarWidget> MyHealthWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Widget | Health")
    UHealthBarWidget *HealthBarWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Pause")
    TSubclassOf<class UPauseWidget> MyPauseMenu;

    UPROPERTY(BlueprintReadOnly, Category = "Widget | Pause")
    class UPauseWidget *PauseMenu;
#pragma endregion

#pragma region Input
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Context")
    class UInputMappingContext *MappingContextComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    class UInputAction *InputActionMove;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionLookAround;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionJump;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionLightAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionHeavyAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionAbilityKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionScrollAbility;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *InputActionOpenCloseInventory;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *PauseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action")
    UInputAction *DebugActionKey;
#pragma endregion

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell | Data")
    int SelectedSpell;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell | Data")
    float GroundSpellLocationOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Spell Enhancement")
    class ABaseSpellActor *SpellEnenhancements;

    void AttachSpellComponents(FName socket_name);

    UPROPERTY(EditDefaultsOnly)
    USoundBase *PickupSound;

    virtual bool ShouldNotifyLanded(const FHitResult &Hit) override;

protected:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int other_index, bool from_sweep, const FHitResult &sweep_result);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent *primitive_component, AActor *other_actor, UPrimitiveComponent *other_component, int i);
    virtual void BeginPlay() override;

    void SetSpell();

#pragma region InputFuncs
    void MoveAction(const FInputActionValue &value);

    void LookAroundAction(const FInputActionValue &value);

    void JumpAction(const FInputActionValue &value);

    void LightAttackAction(const FInputActionValue &value);

    void HeavyAttackAction(const FInputActionValue &value);

    void AbilityKeyAction(const FInputActionValue &value);

    void AbilityScrollAction(const FInputActionValue &value);

    void OpenCloseInventory(const FInputActionValue &value);

    void OpenClosePauseMenu(const FInputActionValue &value);

    void DebugAction(const FInputActionValue &value);
#pragma endregion

public:
    virtual void Tick(float delta_time) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *input_component) override;

    void SetCheckpoint(ACheckpointActor *checkpoint);
};
