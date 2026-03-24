#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LatticeScaleManager.generated.h"

UENUM(BlueprintType)
enum class ELatticeScale : uint8
{
    MACRO   UMETA(DisplayName = "Macro - Human Scale"),
    MICRO   UMETA(DisplayName = "Micro - Insect Scale"),
    NANO    UMETA(DisplayName = "Nano - Cellular Scale"),
    QUANTUM UMETA(DisplayName = "Quantum - Atomic Scale"),
    GEO     UMETA(DisplayName = "Geo - Geological Scale"),
    COSMIC  UMETA(DisplayName = "Cosmic - Planetary Scale")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnScaleChanged,
    ELatticeScale, OldScale,
    ELatticeScale, NewScale
);

UCLASS()
class LATTICE_API ULatticeScaleManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Lattice|Scale")
    FOnScaleChanged OnScaleChanged;

    UFUNCTION(BlueprintCallable, Category = "Lattice|Scale")
    void TransitionToScale(ELatticeScale NewScale);

    UFUNCTION(BlueprintPure, Category = "Lattice|Scale")
    ELatticeScale GetCurrentScale() const { return CurrentScale; }

private:
    ELatticeScale CurrentScale = ELatticeScale::MACRO;
};