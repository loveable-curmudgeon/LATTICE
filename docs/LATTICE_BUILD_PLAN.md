# LATTICE_BUILD_PLAN.md
_Phased development roadmap for LATTICE. Read LATTICE_CONTROL.md first._

---

## How to Use This Document

Each phase has entry criteria (what must be true before starting),
exit criteria (what must be true before moving on), and deliverables.
Do not start a phase until its entry criteria are met.
Do not mark a phase complete until all exit criteria are verified in engine.

---

## Phase 0 — Foundation
**Status: COMPLETE**

### Entry Criteria
- Fresh Unreal Engine 5.7 project

### Exit Criteria
- Project opens in UE 5.7 ?
- C++ compiles clean ?
- Player spawns and moves ?
- All assets committed to git ?

### Deliverables
- LatticeScaleManager (GameInstanceSubsystem)
- LatticePlayerCharacter (ACharacter subclass, Enhanced Input)
- AncientTechDevice (scale transition trigger)
- ELatticeScale enum (six scales defined)
- BP_LatticePlayerCharacter with input bindings
- BP_LatticeGameMode with correct default pawn
- LATTICE_CONTROL.md
- LATTICE_BUILD_PLAN.md

---

## Phase 1 — Core Loop Prototype
**Status: COMPLETE**

The goal of this phase is one complete, playable loop:
spawn ? explore ? find device ? trigger scale transition ? physics change felt ?
find team member ? reach portal ? level ends.
No polish. No puzzles yet. Just the skeleton of the loop working end to end.

### Entry Criteria
- Phase 0 complete

### Exit Criteria
- AncientTechDevice placed in MACRO_Level_01 and triggers scale transition
- Physics change is noticeable when scale changes
- A placeholder team member exists in the level
- A placeholder portal exists in the level
- Reaching the portal ends the level (any basic transition is fine)
- All new assets committed to git

### Deliverables
- AncientTechDevice placed and working in MACRO_Level_01
- Placeholder team member actor
- Placeholder portal actor with level-end trigger
- Basic HUD showing current scale (so player knows transition happened)
- One complete playthrough from spawn to level end possible

### Notes
- Physics values at this stage do not need to be scientifically accurate yet
- Art and level design do not matter here — boxes and BSP are fine
- The point is proving the loop works, not that it looks or feels good

---

## Phase 2 — Character & Companion System
**Status: NOT STARTED**

### Entry Criteria
- Phase 1 complete

### Exit Criteria
- Player can select a character at game start
- At least two characters defined with distinct profiles
- Non-selected characters exist in levels as AI companions
- AI companions follow the player and do not break navigation
- Character selection persists through level transitions
- All assets committed to git

### Deliverables
- Character selection screen (basic UI, no polish needed yet)
- Character data structure (name, profile, mesh slot)
- AI companion controller (follow behavior, basic awareness)
- At least two character meshes or placeholder meshes assigned
- SaveGame integration for character selection persistence

### Notes
- Character backstories and dialog belong in LATTICE-STORY
- Character selection UI will be redesigned in Phase 11 — keep it functional for now
- AI companion complexity will grow in later phases as puzzle interactions are added

---

## Phase 3 — Scale Physics Research & Verification
**Status: NOT STARTED**

This is a research and design phase, not a coding phase.
No scale content gets built until this phase is complete.
The puzzles in LATTICE exist to teach real physics — that means the physics must be
understood and documented before puzzles are designed.

### Entry Criteria
- Phase 2 complete
- LATTICE-DESIGN project created in Claude

### Exit Criteria
- All six scales have a documented physics profile in LATTICE-DESIGN
- Each profile includes: real-world scientific basis, key phenomena the player will experience,
  which normal assumptions break down and why, potential puzzle concepts that emerge naturally
  from the physics
- Physics profiles reviewed and signed off before Phase 4 begins

### Deliverables (in LATTICE-DESIGN, not this repo)
- SCALE_PHYSICS_REFERENCE.md — one section per scale
- MACRO: human scale, baseline Newtonian physics
- MICRO: insect/cellular scale — surface tension dominates, air resistance significant,
  gravity relatively weak, Van der Waals forces present
- NANO: molecular scale — Brownian motion, quantum tunneling begins, thermal noise significant
- QUANTUM: atomic/subatomic — quantum mechanics dominant, probability-based behavior,
  classical physics largely breaks down
- GEO: geological scale — tectonic forces, erosion timescales, gravity dominates everything
- COSMIC: planetary/stellar scale — orbital mechanics, relativity effects, gravity at extremes

### Notes
- This phase will take as long as it needs to — do not rush it
- Consult real physics references, not just intuition
- Each scale's puzzle concepts feed directly into Phase 4

---

## Phase 4 — Puzzle Framework
**Status: NOT STARTED**

### Entry Criteria
- Phase 3 complete
- All six scale physics profiles documented and reviewed

### Exit Criteria
- Core puzzle interaction system built and tested
- At least three distinct puzzle types prototyped in engine
- Puzzle types demonstrably teach a real physics concept
- Puzzle system is extensible to support new types per scale
- All assets committed to git

### Deliverables
- Interaction system (player can interact with puzzle objects)
- Puzzle base class (extensible for scale-specific puzzle types)
- At least three prototype puzzles (one per distinct physics concept)
- Puzzle state tracking (solved/unsolved persists correctly)

### Notes
- Puzzle types must emerge from Phase 3 physics research — do not invent puzzles
  and then try to attach physics to them, it goes the other way
- Each puzzle should have a clear "aha moment" where the player understands
  something real about physics

---

## Phases 5–10 — Scale Content (One Phase Per Scale)

Each scale follows the same pattern:

1. Physics tuned in engine against Phase 3 reference document
2. Level built (environment reflects the scale visually and mechanically)
3. Puzzles designed and placed (teach that scale's physics)
4. Team member and portal placed
5. Narrative hooks connected (see LATTICE-STORY)
6. Full playthrough tested
7. All assets committed

### Phase 5 — MACRO Scale Content
### Phase 6 — MICRO Scale Content
### Phase 7 — NANO Scale Content
### Phase 8 — QUANTUM Scale Content
### Phase 9 — GEO Scale Content
### Phase 10 — COSMIC Scale Content

_Each phase will be detailed fully when it becomes the active phase._

---

## Phase 11 — Polish, UI, Audio, Ship
**Status: NOT STARTED**

_To be detailed when Phase 10 is complete._

Includes: UI redesign, audio implementation, accessibility review,
performance optimization, final playtesting, release build.

---

## Dependency Chain

Foundation ? Core Loop ? Characters ? Physics Research ? Puzzle Framework ? Scale Content ? Ship

Physics research is the backbone of the entire game.
No scale content phase begins without the physics reference for that scale being complete.

---

## Rules for This Document

1. Do not skip phases or start a phase before entry criteria are met
2. Exit criteria must be verified in engine, not just assumed
3. Mark phases complete only when all deliverables exist and are committed to git
4. Each scale phase must begin with a physics review session before any content is built
5. This document is updated at the end of every working session

