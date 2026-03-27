#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LatticePortal.generated.h"

UCLASS()
class LATTICE_API ALatticePortal : public AActor
{
    GENERATED_BODY()

public:
    ALatticePortal();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* TriggerSphere;

    UFUNCTION()
    void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
