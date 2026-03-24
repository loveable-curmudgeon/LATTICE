#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LatticeScaleManager.h"
#include "AncientTechDevice.generated.h"

UCLASS()
class LATTICE_API AAncientTechDevice : public AActor
{
    GENERATED_BODY()

public:
    AAncientTechDevice();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Lattice|Device")
    void Activate();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lattice|Device")
    ELatticeScale TargetScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lattice|Device")
    bool bHasBeenActivated = false;

private:
    UPROPERTY()
    ULatticeScaleManager* ScaleManager;
};
