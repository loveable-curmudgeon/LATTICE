#include "LatticePlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ALatticePlayerCharacter::ALatticePlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALatticePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    ScaleManager = GI->GetSubsystem<ULatticeScaleManager>();

    if (ScaleManager)
    {
        ScaleManager->OnScaleChanged.AddDynamic(this, &ALatticePlayerCharacter::OnScaleChanged);
        ApplyScalePhysics(ScaleManager->GetCurrentScale());
    }
}

void ALatticePlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALatticePlayerCharacter::OnScaleChanged(ELatticeScale OldScale, ELatticeScale NewScale)
{
    ApplyScalePhysics(NewScale);
}

void ALatticePlayerCharacter::ApplyScalePhysics(ELatticeScale Scale)
{
    if (!ScaleManager) return;

    FLatticeScalePhysics Params = ScaleManager->GetPhysicsForScale(Scale);
    UCharacterMovementComponent* Movement = GetCharacterMovement();

    if (Movement)
    {
        Movement->GravityScale            = Params.GravityScale;
        Movement->MaxWalkSpeed            = Params.MovementSpeed;
        Movement->JumpZVelocity           = Params.JumpVelocity;
        Movement->BrakingFrictionFactor   = Params.AirResistance;
    }
}
