#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LatticeHUD.generated.h"

UCLASS()
class LATTICE_API ALatticeHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
