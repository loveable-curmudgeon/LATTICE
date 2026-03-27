#include "LatticePortal.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ALatticePortal::ALatticePortal()
{
    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    TriggerSphere->SetSphereRadius(200.0f);
    TriggerSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    RootComponent = TriggerSphere;
}

void ALatticePortal::BeginPlay()
{
    Super::BeginPlay();
    TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ALatticePortal::OnPlayerEnter);
}

void ALatticePortal::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
    {
        UGameplayStatics::OpenLevel(this, TEXT("MACRO_Level_01"));
    }
}
