// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UInventoryWidget;
class UMinimapWidget;
struct FInputActionValue;

UCLASS()
class BACKROWSTUDIO_API AMainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
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
    class USpringArmComponent *MiniMapSpringArm;

    // |Minimap| SceneCapture Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
    class USceneCaptureComponent2D* MinimapCam;

    // |Minimap| Minimap Widget Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    TSubclassOf<UMinimapWidget> MiniMapWidgetTemplate;

    // |Minimap| Minimap Material
    UPROPERTY(BlueprintReadOnly, Category = "Minimap")
    class UMinimapWidget* MinimapWidget;

    // |Minimap| Minimap Material
    UPROPERTY()
    UMaterial* Mat;

    // |Inventory| Inventory Component
     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    class UInventoryComponent* MyInv;
    bool OpenInventory = true;
    bool CanOpenInventory = true;

    // |Inventory| Inventory Widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TSubclassOf<UInventoryWidget> MyInvWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    UInventoryWidget* InvWidget;

    // Player Controller Reference
    UPROPERTY()
    APlayerController* PC;


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

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionLightAttack;

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionHeavyAttack;

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionAbilityKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionScrollAbility;
    
    // |Input Action| Open or Close Inventory
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionOpenCloseInventory;

    // |Input Action| Open or Close Inventory Helper
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    UInputAction *InputActionOpenCloseInventoryHelper;

     /**
     * Spell Objects
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
    int SelectedSpell;

    // |Spells| Arcane Enhancement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Arcane Enhancement")
    class ABaseSpellActor *ArcaneEnhancement;

    // |Spells| Fire Enhancement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Fire Enhancement")
    class ABaseSpellActor *FireEnhancement;

    // |Spells| Cold Enhancement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Cold Enhancement")
    class ABaseSpellActor *ColdEnhancement;

    // |Spells| Lightning Enhancement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells | Lightning Enhancement")
    class ABaseSpellActor *LightningEnhancement;

    void AttachSpellComponents(/*TSubclassOf<ABaseSpellActor> SpellActors,*/ FName SocketName);


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Action Input Functions
     */
    // Player Move Function
    void MoveAction(const FInputActionValue &Value);

    // Player Look Around Function
    void LookAroundAction(const FInputActionValue &Value);

    // Player Jump Function
    void JumpAction(const FInputActionValue &Value);

    // Player Light Attack Function
    void LightAttackAction(const FInputActionValue &Value);

    // Player Heavy Attack Function
    void HeavyAttackAction(const FInputActionValue &Value);

    // Player Ability Functions
    void AbilityKeyAction(const FInputActionValue &Value);

    void AbilityScrollAction(const FInputActionValue &Value);
    // Open or Close Inventory Function
    void OpenCloseInventory(const FInputActionValue &Value);

    // Open or Close Inventory Helper Function
    void OpenCloseInventoryHelper(const FInputActionValue &Value);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
    // Movement Component
    // UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    // TObjectPtr<UCharacterMovementComponent> CharacterMovement;
};