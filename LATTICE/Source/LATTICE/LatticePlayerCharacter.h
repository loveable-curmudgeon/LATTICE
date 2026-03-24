#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LatticeScaleManager.h"
#include "LatticePlayerCharacter.generated.h"

UCLASS()
class LATTICE_API ALatticePlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ALatticePlayerCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UFUNCTION()
    void OnScaleChanged(ELatticeScale OldScale, ELatticeScale NewScale);

    void ApplyScalePhysics(ELatticeScale Scale);

private:
    UPROPERTY()
    ULatticeScaleManager* ScaleManager;
};
