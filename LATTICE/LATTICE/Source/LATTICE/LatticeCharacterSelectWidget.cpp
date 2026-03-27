#include "LatticeCharacterSelectWidget.h"
#include "LatticeCharacterSave.h"
#include "Kismet/GameplayStatics.h"

void ULatticeCharacterSelectWidget::SelectCharacter(ELatticeCharacter Character)
{
    PendingSelection = Character;
}

void ULatticeCharacterSelectWidget::ConfirmSelection()
{
    if (PendingSelection == ELatticeCharacter::None) return;

    ULatticeCharacterSave* SaveData = Cast<ULatticeCharacterSave>(
        UGameplayStatics::CreateSaveGameObject(ULatticeCharacterSave::StaticClass()));

    if (SaveData)
    {
        SaveData->SelectedCharacter = PendingSelection;
        UGameplayStatics::SaveGameToSlot(SaveData, TEXT("CharacterSlot"), 0);
    }

    RemoveFromParent();
}
