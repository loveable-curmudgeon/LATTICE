#pragma once

#include "CoreMinimal.h"
#include "LatticeCharacterData.generated.h"

UENUM(BlueprintType)
enum class ELatticeCharacter : uint8
{
    None     UMETA(DisplayName = "None"),
    Reyes    UMETA(DisplayName = "Reyes"),
    Okafor   UMETA(DisplayName = "Okafor")
};

USTRUCT(BlueprintType)
struct FLatticeCharacterProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ELatticeCharacter CharacterID = ELatticeCharacter::None;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText ShortBio;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<class ACharacter> CharacterClass;
};
