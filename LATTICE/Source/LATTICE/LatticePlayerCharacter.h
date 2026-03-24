#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LatticeScaleManager.h"
#include "InputActionValue.h"
#include "LatticePlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LATTICE_API ALatticePlayerCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ALatticePlayerCharacter();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    UFUNCTION()
    void OnScaleChanged(ELatticeScale OldScale, ELatticeScale NewScale);
    void ApplyScalePhysics(ELatticeScale Scale);
    void Move(const FInputActionValue& Value);
    void Jump();

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* JumpAction;

private:
    UPROPERTY()
    ULatticeScaleManager* ScaleManager;
};
