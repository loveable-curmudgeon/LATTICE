#include "AncientTechDevice.h"
#include "Kismet/GameplayStatics.h"

AAncientTechDevice::AAncientTechDevice()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAncientTechDevice::BeginPlay()
{
    Super::BeginPlay();

    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    ScaleManager = GI->GetSubsystem<ULatticeScaleManager>();
}

void AAncientTechDevice::Activate()
{
    if (bHasBeenActivated) return;
    if (!ScaleManager) return;

    bHasBeenActivated = true;
    ScaleManager->TransitionToScale(TargetScale);
}
