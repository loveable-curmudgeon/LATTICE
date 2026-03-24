# LATTICE — Project Control Document
*Last updated: 2026-03-23*

---

## 1. Concept

LATTICE is a third-person physics puzzle game inspired by the short film "Powers of Ten."
A joint military/science team investigates ancient technology discovered when a natural
disaster exposes a buried temple. The tech activates and scatters the team across different
physical scales. The player must navigate each scale — where physics behaves differently —
to rescue each team member. Rescued members then assist in subsequent levels.

---

## 2. Tech Stack

| Tool | Version | Notes |
|---|---|---|
| Engine | Unreal Engine 5.7 | C++ / Maximum Quality project |
| IDE | Visual Studio 2022 (v18) | Community edition |
| Repo | GitLab | gitlab.com/loveable_curmudgeon/lattice |
| OS | Windows 11 | Developer PowerShell for CLI work |
| Git LFS | Enabled | For large binary assets |

---

## 3. Locked Design Decisions

| Question | Decision |
|---|---|
| Scale transition trigger | Player interacts with ancient tech device |
| Number of scales | 6 |
| Player perspective | Third-person |
| Team scatter method | Natural disaster triggers ancient tech — random scatter |
| Level order | Linear — one scale unlocks the next |

---

## 4. The 6 Scales

| Order | Scale | Size Reference | Dominant Physics |
|---|---|---|---|
| 1 | MACRO | Human / temple | Normal physics — tutorial / home base |
| 2 | MICRO | Insect / dust grain | Surface tension, Van der Waals adhesion, relative strength multiplied |
| 3 | NANO | Cellular / molecular | Brownian motion, diffusion, osmosis, thermal noise visible |
| 4 | QUANTUM | Atomic / sub-atomic | Tunneling, superposition, wave-particle duality, probability-based movement |
| 5 | GEO | Geological / city-sized | Rock flows like fluid, extreme pressure, seismic waves, tectonic forces |
| 6 | COSMIC | Planetary / stellar | Gravity dominates, orbital mechanics, no air resistance, tidal forces |

Level arc: start familiar ? go smaller and stranger ? swing to enormous for the finale.
COSMIC is the final reveal — the ancient tech's true origin.

---

## 5. Physics Parameters Per Scale

Defined in LatticeScaleManager.cpp — GetPhysicsForScale()

| Scale | GravityScale | MovementSpeed | JumpVelocity | AirResistance |
|---|---|---|---|---|
| MACRO | 1.0 | 600 | 700 | 0.01 |
| MICRO | 0.2 | 400 | 1200 | 0.8 |
| NANO | 0.05 | 200 | 1800 | 2.0 |
| QUANTUM | 0.001 | 100 | 2400 | 0.0 |
| GEO | 4.0 | 1200 | 400 | 0.0 |
| COSMIC | 0.0 | 2000 | 0 | 0.0 |

---

## 6. Content Folder Structure
```
Content/
+-- AncientTech/
+-- Characters/
¦   +-- Player/
¦   +-- TeamNPC/
¦   +-- Shared/
+-- Core/
¦   +-- GameMode/
¦   +-- ScaleSystem/
¦   +-- Physics/
¦   +-- SaveGame/
+-- Scales/
¦   +-- MACRO/   (Blueprints/ Maps/ Assets/)
¦   +-- MICRO/   (Blueprints/ Maps/ Assets/)
¦   +-- NANO/    (Blueprints/ Maps/ Assets/)
¦   +-- QUANTUM/ (Blueprints/ Maps/ Assets/)
¦   +-- GEO/     (Blueprints/ Maps/ Assets/)
¦   +-- COSMIC/  (Blueprints/ Maps/ Assets/)
+-- Shared/
```

---

## 7. C++ Classes Written

All source files live in: Source/LATTICE/

### LatticeScaleManager (.h / .cpp)
- Parent: UGameInstanceSubsystem
- Purpose: Single source of truth for current scale. Persists across level loads.
- Key members:
  - ELatticeScale enum — MACRO, MICRO, NANO, QUANTUM, GEO, COSMIC
  - FLatticeScalePhysics struct — GravityScale, MovementSpeed, JumpVelocity, AirResistance
  - FOnScaleChanged delegate — broadcast when scale changes
  - TransitionToScale(ELatticeScale) — call this to shift scales
  - GetCurrentScale() — returns current scale
  - GetPhysicsForScale(ELatticeScale) — returns physics params for any scale

### LatticePlayerCharacter (.h / .cpp)
- Parent: ACharacter
- Purpose: The player's third-person character. Listens for scale changes and
  applies new physics parameters to the CharacterMovementComponent instantly.
- Key flow: BeginPlay ? gets ScaleManager ? binds OnScaleChanged delegate ?
  ApplyScalePhysics() updates GravityScale, MaxWalkSpeed, JumpZVelocity,
  BrakingFrictionFactor on the movement component.

### LatticeGameMode (.h / .cpp)
- Parent: AGameModeBase
- Purpose: Sets ALatticePlayerCharacter as DefaultPawnClass.
  Must be set as default GameMode in Project Settings.

### AncientTechDevice (.h / .cpp)
- Parent: AActor
- Purpose: Placeable actor in levels. When Activate() is called (by player
  interaction), it tells the ScaleManager to transition to TargetScale.
  Can only be activated once (bHasBeenActivated flag).
- Key properties (editable in Unreal):
  - TargetScale — which scale this device sends the player to
  - bHasBeenActivated — prevents double activation

---

## 8. How the Systems Connect

Player finds device
  ? Activate() called on AncientTechDevice
  ? AncientTechDevice calls ScaleManager->TransitionToScale(TargetScale)
  ? ScaleManager updates CurrentScale
  ? ScaleManager broadcasts OnScaleChanged delegate
  ? LatticePlayerCharacter hears broadcast
  ? ApplyScalePhysics() applies new physics values to movement component

---

## 9. What Has NOT Been Done Yet

- [ ] Set LatticeGameMode as default in Project Settings (Unreal Editor)
- [ ] Create first playable map (MACRO level)
- [ ] Place AncientTechDevice in map and test scale transition
- [ ] Player input / camera setup (third-person camera boom + spring arm)
- [ ] Team NPC base class
- [ ] Save/load system
- [ ] UI / HUD
- [ ] Any art assets
- [ ] Puzzle design for any scale

---

## 10. Immediate Next Steps (start here in new session)

1. Open Unreal Editor ? Project Settings ? Maps & Modes
2. Set Default GameMode to LatticeGameMode
3. Create a new level saved to Content/Scales/MACRO/Maps/
4. Place an AncientTechDevice in the level
5. Test that activating it changes the scale and physics

---

## 11. Conventions & Notes

- Regina is a solo dev with beginner coding knowledge — keep steps small
- Windows 11 / PowerShell — no bash/Linux commands
- Use Developer PowerShell (from Visual Studio Tools menu) for CLI work
- Use heredoc style (@' '@) for writing code files from PowerShell
- Compile method: Ctrl+Alt+F11 in Unreal Editor (Live Coding)
- Avoid nano — Regina prefers CLI tools
- LF/CRLF warnings on git add are harmless, ignore them
- Always commit and push at the end of each working session
