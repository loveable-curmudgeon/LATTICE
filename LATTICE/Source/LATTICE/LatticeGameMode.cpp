#include "LatticeGameMode.h"
#include "LatticePlayerCharacter.h"

ALatticeGameMode::ALatticeGameMode()
{
    DefaultPawnClass = ALatticePlayerCharacter::StaticClass();
}
