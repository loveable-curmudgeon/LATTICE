#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LatticeGameMode.generated.h"

UCLASS()
class LATTICE_API ALatticeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ALatticeGameMode();

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<class UUserWidget> CharacterSelectWidgetClass;
};
