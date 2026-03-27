#include "LatticeGameMode.h"
#include "LatticePlayerCharacter.h"
#include "LatticeCharacterSave.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ALatticeGameMode::ALatticeGameMode()
{
    DefaultPawnClass = ALatticePlayerCharacter::StaticClass();
}

void ALatticeGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (!CharacterSelectWidgetClass) return;

    ULatticeCharacterSave* SaveData = Cast<ULatticeCharacterSave>(
        UGameplayStatics::LoadGameFromSlot(TEXT("CharacterSlot"), 0));

    bool bNeedsSelection = !SaveData || SaveData->SelectedCharacter == ELatticeCharacter::None;

    if (bNeedsSelection)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), CharacterSelectWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
        }
    }
}
