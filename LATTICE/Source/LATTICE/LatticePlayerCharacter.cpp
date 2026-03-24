#include "LatticePlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

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
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ALatticePlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALatticePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALatticePlayerCharacter::Move);
        EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALatticePlayerCharacter::Jump);
    }
}

void ALatticePlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void ALatticePlayerCharacter::Jump()
{
    ACharacter::Jump();
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
        Movement->GravityScale          = Params.GravityScale;
        Movement->MaxWalkSpeed          = Params.MovementSpeed;
        Movement->JumpZVelocity         = Params.JumpVelocity;
        Movement->BrakingFrictionFactor = Params.AirResistance;
    }
}
