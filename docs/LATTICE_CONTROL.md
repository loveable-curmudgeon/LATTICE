# LATTICE_CONTROL.md
_Master context document. Every new chat session working on LATTICE-CODE must read this first._

---

## Project Overview

**LATTICE** is a single-player, third-person educational physics puzzle game built in Unreal Engine 5.7.

Inspired by the short film *Powers of Ten*, the game follows a joint military/science team
investigating ancient technology uncovered after a natural disaster exposes a buried temple.
The tech sends team members to different physical scales — from human scale down to atomic,
and up to geological and cosmic. Physics behaves differently at each scale, grounded in real
science. The player must solve scale-specific puzzles to locate and rescue team members, who
then join future levels as playable or supporting characters.

LATTICE is an educational game first. The goal is to make educational games that are actually
fun. Physics accuracy is a core design value — parameters must be scientifically grounded, not
just whatever feels good. A separate reference document in LATTICE-DESIGN tracks the scientific
basis for each scale's physics profile.

This is a long-term solo project.

---

## Developer Profile

- **Developer:** Regina (solo)
- **Background:** Engineering degree, college-level C++ knowledge, beginner Unreal experience
- **OS:** Windows 11
- **Engine:** Unreal Engine 5.7
- **IDE:** Visual Studio 2022
- **CLI:** Developer PowerShell (from Windows search, NOT from inside Visual Studio)
- **Repo:** gitlab.com/loveable_curmudgeon/lattice
- **Project path:** `C:\Users\megan\Documents\lattice\LATTICE\LATTICE`
- **Git note:** Repo root is `lattice\`. Unreal project lives at `lattice\LATTICE\LATTICE\`.
  Control docs live at `lattice\docs\`. Git commands run from repo root.

---

## Hardware Notes

- 16GB RAM — close all other apps before opening Unreal
- No browser, Discord, or Spotify while working
- Skip "restore asset editors" prompt on launch (can cause crashes)
- Save frequently with Ctrl+S

---

## Compile & Run

- **Live compile:** `Ctrl+Alt+F11` inside Unreal Editor
- **If Live Coding fails:** close Unreal, reopen LATTICE.uproject for full recompile
- **Target:** `LATTICEEditor Win64 Development`
- **Play in Editor:** Green Play button in Unreal Editor toolbar
- **Write files via CLI:** heredoc `@' '@` piped to Set-Content in Developer PowerShell

---

## Project Structure (Three Claude Projects)

| Project | Purpose |
|---|---|
| **LATTICE-CODE** (this project) | Engine, C++, Blueprints, systems architecture, build plan |
| **LATTICE-STORY** | Lore bible, character profiles, dialog, world history, narrative |
| **LATTICE-DESIGN** | Game design document, puzzle specs, level briefs, physics reference — bridges mechanics and story |

Design decisions must respect both code constraints and story logic. When they conflict,
open LATTICE-DESIGN to resolve it.

---

## Architecture Overview

### Core Philosophy
- **Make LATTICE excellent** — purpose-built decisions are fine, do not sacrifice quality for reusability
- **Reusability is a bonus, not a goal** — if something is naturally reusable, great, but don't engineer for it
- **C++ for systems** — anything that needs to be fast, shared, or data-driven
- **Blueprint for content** — level-specific logic, designer-facing configuration, one-off behaviors
- **Physics accuracy is non-negotiable** — every scale must reflect real science

### Key Systems

#### LatticeScaleManager (GameInstanceSubsystem)
- Lives on the GameInstance — persists across level loads
- Single source of truth for current scale state
- Broadcasts `OnScaleChanged` delegate when scale transitions occur
- All other systems react to this delegate rather than polling
- **Why a subsystem:** Avoids singleton anti-patterns, automatically available to any class
  that has a GameInstance reference, survives level transitions

#### LatticePlayerCharacter (ACharacter subclass)
- Listens to `OnScaleChanged` and applies physics parameters
- Uses Enhanced Input system (IMC_Default, IA_Move, IA_Jump, IA_Look)
- Physics per scale defined in `FLatticeScalePhysics` struct inside LatticeScaleManager
- Sets "Player" actor tag in BeginPlay

#### AncientTechDevice (AActor subclass)
- Placed in levels as the trigger for scale transitions
- Has a USphereComponent (radius 200) that triggers on player overlap
- Collision set to OverlapAllDynamic
- Calls `ScaleManager->TransitionToScale(TargetScale)` on activation
- One-shot by default (`bHasBeenActivated` flag)
- Requires the player actor to have the tag "Player" to trigger
- **NOTE:** Debug UE_LOG statements still in AncientTechDevice.cpp — remove before release

#### Scale Enum (ELatticeScale)
Six scales defined: MACRO, MICRO, NANO, QUANTUM, GEO, COSMIC
Each has its own physics profile. MACRO is human scale and the starting point.
Physics values must be reviewed against real science before any scale goes into active development.

---

## Scale Physics Values (current — not yet scientifically verified)

| Scale   | Gravity | Speed | Jump | Air Resistance |
|---------|---------|-------|------|----------------|
| MACRO   | 1.0     | 600   | 700  | 0.01           |
| MICRO   | 0.6     | 400   | 500  | 0.05           |
| NANO    | 0.3     | 200   | 300  | 0.2            |
| QUANTUM | 0.1     | 100   | 200  | 0.5            |
| GEO     | 2.0     | 1200  | 1400 | 0.001          |
| COSMIC  | 0.05    | 2000  | 100  | 0.0            |

---

## Blueprint Assets (must be committed to git immediately after creation)

### BP_LatticePlayerCharacter — Content/Characters/Player/
- Inherits LatticePlayerCharacter
- Spring Arm: Length 300, Socket Offset Z: 60, Use Pawn Control Rotation: true
- Camera attached to Spring Arm
- Class Defaults: MoveAction=IA_Move, JumpAction=IA_Jump, LookAction=IA_Look
- Has "Player" actor tag assigned
- **GOTCHA:** Blueprint input assignments clear on recompile — always check Class Defaults after rebuild

### BP_LatticeGameMode — Content/Core/GameMode/
- Default Pawn Class: BP_LatticePlayerCharacter
- Set as default GameMode in Project Settings > Maps & Modes

---

## Input Assets (Content/Core/)

- `IMC_Default` — Input Mapping Context
  - `IA_Move` — WASD. S and A keys have Negate modifier. W has Swizzle+Negate.
  - `IA_Jump` — Spacebar
  - `IA_Look` — Mouse XY 2D-Axis

---

## Levels

### MACRO_Level_01 — Content/Scales/MACRO/Maps/
- Floor plane: Location 0,0,0, Scale 50,50,1, material M_PurpleFloor
- AncientTechDevice placed and working — walk into it triggers scale transition
- Physics transition verified via UE_LOG (2026-03-24)

---

## Current State (as of 2026-03-24)

| Item | Status |
|---|---|
| Project opens in UE 5.7 | YES |
| C++ compiles clean | YES |
| Player spawns and moves | YES |
| Mouse look working in Play mode | YES |
| BP_LatticePlayerCharacter committed to git | YES |
| BP_LatticeGameMode committed to git | YES |
| AncientTechDevice placed in level | YES |
| AncientTechDevice visible mesh | YES |
| Scale transition tested in game | YES |
| MACRO_Level_01 playable | PARTIAL — floor, spawn, device, mouse look, physics verified |
| Physics values reviewed against real science | NO |
| Debug UE_LOG removed from AncientTechDevice.cpp | NO |

---

## Active Phase

**Phase 1 — Core Loop Prototype: COMPLETE**

Next: Begin Phase 2 — Character & Companion System

See `docs/LATTICE_BUILD_PLAN.md` for full phase breakdown.

---

## Rules for This Project

1. **Read this document at the start of every session before giving any advice or writing any code**
2. **Explain the why, not just the what** — every architectural decision should be documented here
3. **Small steps** — a few tasks at a time, confirm working before moving on
4. **Don't invent status** — if something has not been tested, mark it NO or PARTIAL, not YES
5. **Commit Blueprint assets immediately** after creation — they do not auto-track in git
6. **Update Current State table** at the end of each working session
7. **Do not redesign existing systems** without flagging it explicitly and getting confirmation
8. **Physics accuracy first** — when in doubt, research the real science before implementing

---

## Known Gotchas

- `.uasset` files are binary — git LFS is active on this repo, that is expected and correct
- `BP_LatticePlayerCharacter` was lost in a crash/reclone because it was not committed — always commit Blueprint assets immediately
- Developer PowerShell is accessed from Windows search, not from inside Visual Studio
- Blueprint input assignments (MoveAction, JumpAction, LookAction) clear on recompile — always recheck Class Defaults after rebuild
- Debug UE_LOG statements still in AncientTechDevice.cpp — remove before release
- Control docs live in `docs/` at repo root, not inside the LATTICE project folder
