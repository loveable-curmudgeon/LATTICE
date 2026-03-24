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

FLatticeScalePhysics ULatticeScaleManager::GetPhysicsForScale(ELatticeScale Scale) const
{
    FLatticeScalePhysics Params;

    switch (Scale)
    {
    case ELatticeScale::MACRO:
        Params.GravityScale = 1.0f;
        Params.MovementSpeed = 600.0f;
        Params.JumpVelocity = 700.0f;
        Params.AirResistance = 0.01f;
        break;

    case ELatticeScale::MICRO:
        Params.GravityScale = 0.2f;
        Params.MovementSpeed = 400.0f;
        Params.JumpVelocity = 1200.0f;
        Params.AirResistance = 0.8f;
        break;

    case ELatticeScale::NANO:
        Params.GravityScale = 0.05f;
        Params.MovementSpeed = 200.0f;
        Params.JumpVelocity = 1800.0f;
        Params.AirResistance = 2.0f;
        break;

    case ELatticeScale::QUANTUM:
        Params.GravityScale = 0.001f;
        Params.MovementSpeed = 100.0f;
        Params.JumpVelocity = 2400.0f;
        Params.AirResistance = 0.0f;
        break;

    case ELatticeScale::GEO:
        Params.GravityScale = 4.0f;
        Params.MovementSpeed = 1200.0f;
        Params.JumpVelocity = 400.0f;
        Params.AirResistance = 0.0f;
        break;

    case ELatticeScale::COSMIC:
        Params.GravityScale = 0.0f;
        Params.MovementSpeed = 2000.0f;
        Params.JumpVelocity = 0.0f;
        Params.AirResistance = 0.0f;
        break;
    }

    return Params;
}