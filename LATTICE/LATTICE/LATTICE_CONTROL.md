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
- **Project path:** `C:\Users\megan\Documents\lattice\LATTICE`
- **Git note:** Repo root is `LATTICE\` but project files live one level deeper at `LATTICE\LATTICE\`.
  Git commands run from repo root must use `LATTICE/Content/...` paths.

---

## Compile & Run

- **Live compile:** `Ctrl+Alt+F11` inside Unreal Editor
- **Target:** `LATTICEEditor Win64 Development`
- **Play in Editor:** Green Play button in Unreal Editor toolbar

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
- Uses Enhanced Input system (IMC_Default, IA_Move, IA_jump)
- Physics per scale defined in `FLatticeScalePhysics` struct inside LatticeScaleManager

#### AncientTechDevice (AActor subclass)
- Placed in levels as the trigger for scale transitions
- Has a USphereComponent (radius 200) that triggers on player overlap
- Calls `ScaleManager->TransitionToScale(TargetScale)` on activation
- One-shot by default (`bHasBeenActivated` flag)
- Requires the player actor to have the tag "Player" to trigger

#### Scale Enum (ELatticeScale)
Six scales defined: MACRO, MICRO, NANO, QUANTUM, GEO, COSMIC
Each has its own physics profile. MACRO is human scale and the starting point.
Physics values must be reviewed against real science before any scale goes into active development.

### Blueprint Assets (must be committed to git immediately after creation)
- `BP_LatticePlayerCharacter` — inherits LatticePlayerCharacter, has input assets assigned, has "Player" tag
- `BP_LatticeGameMode` — sets BP_LatticePlayerCharacter as Default Pawn Class

### Input Assets (Content/Core/)
- `IMC_Default` — Input Mapping Context
- `IA_Move` — Move action
- `IA_jump` — Jump action

---

## Current State (as of 2026-03-24)

| Item | Status |
|---|---|
| Project opens in UE 5.7 | YES |
| C++ compiles clean | YES |
| Player spawns and moves | YES |
| BP_LatticePlayerCharacter committed to git | YES |
| BP_LatticeGameMode committed to git | YES |
| Scale transition tested in game | YES |
| AncientTechDevice placed in level | YES |
| AncientTechDevice visible mesh | YES |
| MACRO_Level_01 playable | PARTIAL - floor, spawn, device, mouse look, physics verified |
| Mouse look working in Play mode | YES |
| Physics values reviewed against real science | NO |

---

## Active Phase

**Phase 1 - Core Loop Prototype — COMPLETE**

Phase 1 complete. Next tasks:
- Begin Phase 2: Character & Companion System



See `LATTICE_BUILD_PLAN.md` for full phase breakdown.

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
- Git pathspec must include the inner `LATTICE/` prefix when run from repo root
- AncientTechDevice has no visible mesh yet — it is invisible in Play mode but the trigger sphere works
- Mouse look does not work in Play mode yet — needs investigation
