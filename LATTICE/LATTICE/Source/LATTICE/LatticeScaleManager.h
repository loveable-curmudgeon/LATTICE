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

USTRUCT(BlueprintType)
struct FLatticeScalePhysics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float GravityScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float MovementSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float JumpVelocity = 700.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float AirResistance = 0.01f;
};

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
    UFUNCTION(BlueprintPure, Category = "Lattice|Scale")
    FLatticeScalePhysics GetPhysicsForScale(ELatticeScale Scale) const;

private:
    ELatticeScale CurrentScale = ELatticeScale::MACRO;
};