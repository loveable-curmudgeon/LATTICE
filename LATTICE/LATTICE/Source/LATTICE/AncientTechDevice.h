#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lattice|Device")
    UStaticMeshComponent* Mesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lattice|Device")
    USphereComponent* TriggerSphere;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lattice|Device")
    ELatticeScale TargetScale;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lattice|Device")
    bool bHasBeenActivated = false;
private:
    UPROPERTY()
    ULatticeScaleManager* ScaleManager;
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
