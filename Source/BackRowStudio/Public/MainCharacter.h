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

UCLASS()
class BACKROWSTUDIO_API AMainCharacter : public ACharacter, public IGenericTeamAgentInterface

{
    GENERATED_BODY()

private:

public:
    FGenericTeamId TeamID = FGenericTeamId(1);

    float Health = 100;

    float MaxHealth = 100;

    bool OpenOrClosePause;

    // Sets default values for this character's properties
    AMainCharacter();

    // |Camera| Spring Arm Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent *SpringArmComponent;

    // |Camera| Camera Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent *CameraComponent;

    // |Minimap| Spring Arm Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
    USpringArmComponent *MiniMapSpringArm;

    // |Minimap| SceneCapture Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
    USceneCaptureComponent2D *MinimapCam;

    // |Minimap| Minimap Widget Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    TSubclassOf<UMinimapWidget> MiniMapWidgetTemplate;

    // |Minimap| Minimap Material
    UPROPERTY(BlueprintReadOnly, Category = "Minimap")
    UMinimapWidget *MinimapWidget;

    // |Inventory| Inventory Component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    class UInventoryComponent *MyInv;

    bool OpenInventory = true;

    bool CanOpenInventory = true;

    // |Inventory| Inventory Widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TSubclassOf<UInventoryWidget> MyInvWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    UInventoryWidget *InvWidget;

    // |Health Bar| Health Bar Widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Widget")
    TSubclassOf<UHealthBarWidget> MyHealthWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Health Widget")
    UHealthBarWidget *HealthBarWidget;

    // |Pause Menu| Pause Menu Widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pause Widget")
    TSubclassOf<class UPauseWidget> MyPauseMenu;

    UPROPERTY(BlueprintReadOnly, Category = "Pause Widget")
    class UPauseWidget *PauseMenu;

    // Player Controller Reference
    UPROPERTY()
    APlayerController *PC;


    // |Input| Mapping Context Component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext *MappingContextComponent;

    /**
     * Input Actions
     */
    // |Input Action| Move
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionMove;

    // |Input Action| Look Around
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionLookAround;

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionJump;

    // |Input Action| Light Attack
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionLightAttack;

    // |Input Action| Heavy Attack
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionHeavyAttack;

    // |Input Action| Ability Keys
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionAbilityKey;

    // |Input Action| Ability Scroll Wheel Trigger
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionScrollAbility;

    // |Input Action| Open or Close Inventory
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionOpenCloseInventory;


    // |Input Action| Open or Close Pause Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *PauseAction;

    /**
     * Spell Objects
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
    int SelectedSpell;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    float GroundSpellLocationOffset = 100.f;

    // |Spells| Arcane Enhancement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Spell Enhancement")
    class ABaseSpellActor *SpellEnenhancements;

    //// |Spells| Arcane Enhancement
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Arcane Enhancement")
    // class ABaseSpellActor *ArcaneEnhancement;

    //// |Spells| Fire Enhancement
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Fire Enhancement")
    // class ABaseSpellActor *FireEnhancement;

    //// |Spells| Cold Enhancement
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Cold Enhancement")
    // class ABaseSpellActor *ColdEnhancement;

    //// |Spells| Lightning Enhancement
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Lightning Enhancement")
    // class ABaseSpellActor *LightningEnhancement;

    void AttachSpellComponents(/*TSubclassOf<ABaseSpellActor> SpellActors,*/ FName socket_name);

    UPROPERTY(EditDefaultsOnly)
    USoundBase *PickupSound;

protected:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor,
                        UPrimitiveComponent *other_component, int other_index, bool from_sweep,
                        const FHitResult &sweep_result);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Action Input Functions
     */
    // Player Move Function
    void MoveAction(const FInputActionValue &value);

    // Player Look Around Function
    void LookAroundAction(const FInputActionValue &value);

    // Player Jump Function
    void JumpAction(const FInputActionValue &value);

    // Player Light Attack Function
    void LightAttackAction(const FInputActionValue &value);

    // Set Spell from Spell Inventory
    void SetSpell();

    // Player Heavy Attack Function
    void HeavyAttackAction(const FInputActionValue &value);

    // Player Ability Functions
    void AbilityKeyAction(const FInputActionValue &value);

    // Player Ability Scroll Functions
    void AbilityScrollAction(const FInputActionValue &value);

    // Open or Close Inventory Function
    void OpenCloseInventory(const FInputActionValue &value);

    // Open or Close Pause Menu Function
    void OpenClosePauseMenu(const FInputActionValue &value);

public:
    // Called every frame
    virtual void Tick(float delta_time) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *input_component) override;

private:
    // Movement Component
    // UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    // TObjectPtr<UCharacterMovementComponent> CharacterMovement;
};
