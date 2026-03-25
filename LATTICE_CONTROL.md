# LATTICE — Project Control Document
*Last updated: 2026-03-24*
## 1. Concept
LATTICE is a third-person physics puzzle game inspired by "Powers of Ten."
A joint military/science team investigates ancient technology discovered when a
natural disaster exposes a buried temple. The tech activates and scatters the team
across different physical scales. The player navigates each scale — where physics
behaves differently — to rescue each team member.
## 2. Tech Stack
| Tool | Version | Notes |
|---|---|---|
| Engine | Unreal Engine 5.7 | C++ / Maximum Quality project |
| IDE | Visual Studio 2022 | Community edition |
| Repo | GitLab | gitlab.com/loveable_curmudgeon/lattice |
| OS | Windows 11 | Developer PowerShell for CLI work |
| Git LFS | Enabled | For large binary assets |
## 3. Hardware Notes
- 16GB RAM — close all other apps before opening Unreal
- No browser, Discord, Spotify while working
- Skip "restore asset editors" prompt on launch (can cause crashes)
- Save frequently with Ctrl+S
## 4. Dev Environment
- Compile: Ctrl+Alt+F11 (Live Coding) in Unreal Editor
- If Live Coding fails: close Unreal, reopen LATTICE.uproject for full recompile
- CLI: Developer PowerShell from Visual Studio Tools menu
- Write files using heredoc: @' '@ piped to Set-Content
- LF/CRLF warnings on git add are harmless
## 5. Project Structure
- Project root: C:\Users\megan\Documents\lattice\LATTICE
- GitLab: gitlab.com/loveable_curmudgeon/lattice
- Control doc: LATTICE_CONTROL.md in project root
## 6. C++ Classes (all complete and in GitLab)
- LatticeScaleManager — tracks current scale, broadcasts changes
- LatticePlayerCharacter — applies physics on scale change, sets Player tag in BeginPlay
- LatticeGameMode — sets player character
- AncientTechDevice — triggers scale transitions when activated (collision: OverlapAllDynamic)
## 7. Scale Physics Values
| Scale | Gravity | Speed | Jump | Air Resistance |
|---|---|---|---|---|
| MACRO | 1.0 | 600 | 700 | 0.01 |
| MICRO | 0.6 | 400 | 500 | 0.05 |
| NANO | 0.3 | 200 | 300 | 0.2 |
| QUANTUM | 0.1 | 100 | 200 | 0.5 |
| GEO | 2.0 | 1200 | 1400 | 0.001 |
| COSMIC | 0.05 | 2000 | 100 | 0.0 |
## 8. Blueprints (complete — in GitLab)
- BP_LatticePlayerCharacter: Content/Characters/Player/
  - Spring Arm (Length: 300, Socket Offset Z: 60, Use Pawn Control Rotation: true)
  - Camera attached to Spring Arm
  - Class Defaults: MoveAction=IA_Move, JumpAction=IA_Jump, LookAction=IA_Look
  - GOTCHA: Blueprint input assignments clear on recompile — always check Class Defaults after rebuild
- BP_LatticeGameMode: Content/Core/GameMode/
  - Default Pawn Class: BP_LatticePlayerCharacter
  - Set as default GameMode in Project Settings > Maps & Modes
## 9. Input (complete — in GitLab)
- Enhanced Input system
- IMC_Default input mapping context: Content/Core/
  - IA_Move (WASD — S and A keys have Negate modifier, W has Swizzle+Negate)
  - IA_Jump (Spacebar)
  - IA_Look (Mouse XY 2D-Axis)
## 10. Levels
- MACRO_Level_01: Content/Scales/MACRO/Maps/
  - Floor plane: Location 0,0,0 Scale 50,50,1 — material M_PurpleFloor
  - AncientTechDevice placed and working — walk into it triggers scale transition
  - Physics transition verified via UE_LOG (2026-03-24)
  - NOTE: debug UE_LOG statements still in AncientTechDevice.cpp — remove before release
## 11. Immediate Next Steps (Phase 2)
1. Remove debug UE_LOG statements from AncientTechDevice.cpp
2. Design and build out MACRO scale environment
3. Add visual/audio feedback on scale transition
4. Add additional AncientTechDevice instances with different TargetScale values
5. Begin MICRO scale level
