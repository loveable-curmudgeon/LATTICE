#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LatticeCharacterData.h"
#include "LatticeCharacterSave.generated.h"

UCLASS()
class LATTICE_API ULatticeCharacterSave : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    ELatticeCharacter SelectedCharacter = ELatticeCharacter::None;
};
