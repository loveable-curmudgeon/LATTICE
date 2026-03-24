#include "LatticeScaleManager.h"

void ULatticeScaleManager::TransitionToScale(ELatticeScale NewScale)
{
    if (NewScale == CurrentScale)
    {
        return;
    }

    ELatticeScale OldScale = CurrentScale;
    CurrentScale = NewScale;

    OnScaleChanged.Broadcast(OldScale, NewScale);
}