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
- LatticePlayerCharacter — applies physics on scale change
- LatticeGameMode — sets player character
- AncientTechDevice — triggers scale transitions when activated

## 7. Scale Physics Values
| Scale | Gravity | Speed | Jump | Air Resistance |
|---|---|---|---|---|
| MACRO | 1.0 | 600 | 700 | 0.01 |
| MICRO | 0.6 | 400 | 500 | 0.05 |
| NANO | 0.3 | 200 | 300 | 0.2 |
| QUANTUM | 0.1 | 100 | 200 | 0.5 |
| GEO | 2.0 | 1200 | 1400 | 0.001 |
| COSMIC | 0.05 | 2000 | 100 | 0.0 |

## 8. Blueprints (need to be recreated in new session)
These were lost in crash — need to redo in this order:
1. BP_LatticePlayerCharacter (parent: LatticePlayerCharacter)
   - Add Spring Arm component (Target Arm Length: 300, Socket Offset Z: 60, Use Pawn Control Rotation: true)
   - Add Camera component attached to Spring Arm
2. BP_LatticeGameMode (parent: LatticeGameMode)
   - Set Default Pawn Class to BP_LatticePlayerCharacter
3. Set BP_LatticeGameMode as Default GameMode in Project Settings ? Maps & Modes

## 9. Input (need to be redone in new session)
- Enhanced Input system
- IMC_Default input mapping context
- IA_Move action (WASD — S key has Negate modifier)
- IA_Jump action (Spacebar)

## 10. Levels
- MACRO_Level_01 exists in Content Browser
- AncientTechDevice needs to be placed again
- Scale transition was previously tested and working

## 11. Immediate Next Steps (start here)
1. Create BP_LatticePlayerCharacter in Content/Characters/Player/
2. Add Spring Arm + Camera to it
3. Create BP_LatticeGameMode in Content/Core/GameMode/
4. Set Default Pawn Class in BP_LatticeGameMode
5. Set BP_LatticeGameMode as default in Project Settings
6. Redo Enhanced Input (IMC_Default, IA_Move, IA_Jump)
7. Place AncientTechDevice in MACRO_Level_01
8. Add third-person camera controls (mouse look)
