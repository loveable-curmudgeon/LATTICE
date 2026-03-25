#include "AncientTechDevice.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AAncientTechDevice::AAncientTechDevice()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetSimulatePhysics(false);

    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    TriggerSphere->SetupAttachment(RootComponent);
    TriggerSphere->SetSphereRadius(200.0f);
    TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AAncientTechDevice::OnOverlapBegin);
}

void AAncientTechDevice::BeginPlay()
{
    Super::BeginPlay();
    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    ScaleManager = GI->GetSubsystem<ULatticeScaleManager>();
}

void AAncientTechDevice::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
    {
        Activate();
    }
}

void AAncientTechDevice::Activate()
{
    if (bHasBeenActivated) return;
    if (!ScaleManager) return;
    bHasBeenActivated = true;
    ScaleManager->TransitionToScale(TargetScale);
}
