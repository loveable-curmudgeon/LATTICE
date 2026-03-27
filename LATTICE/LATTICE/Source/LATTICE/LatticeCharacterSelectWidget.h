#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LatticeCharacterData.h"
#include "LatticeCharacterSelectWidget.generated.h"

UCLASS()
class LATTICE_API ULatticeCharacterSelectWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SelectCharacter(ELatticeCharacter Character);

    UFUNCTION(BlueprintCallable)
    void ConfirmSelection();

private:
    ELatticeCharacter PendingSelection = ELatticeCharacter::None;
};
