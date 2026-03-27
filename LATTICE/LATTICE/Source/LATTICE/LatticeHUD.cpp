#include "LatticeHUD.h"
#include "LatticeScaleManager.h"
#include "Engine/Canvas.h"
#include "Engine/GameInstance.h"

void ALatticeHUD::DrawHUD()
{
    Super::DrawHUD();

    ULatticeScaleManager* ScaleManager = GetGameInstance()->GetSubsystem<ULatticeScaleManager>();
    if (!ScaleManager) return;

    FString ScaleName = UEnum::GetValueAsString(ScaleManager->GetCurrentScale());

    // Strip the enum prefix (e.g. "ELatticeScale::MACRO" -> "MACRO")
    FString DisplayName;
    ScaleName.Split(TEXT("::"), nullptr, &DisplayName);

    FString HUDText = FString::Printf(TEXT("SCALE: %s"), *DisplayName);

    DrawText(HUDText, FLinearColor::White, 40.0f, 40.0f, nullptr, 1.5f);
}
