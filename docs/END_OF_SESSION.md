# END_OF_SESSION.md
_Run this at the end of every working session. Takes ~2 minutes._
_You are allowed to be tired. Keep answers short._

---

## Checklist

- [ ] Update **Next 3 Actions** in LATTICE_SESSION_HANDOFF.md
- [ ] Update **Last Session** date and one-sentence summary
- [ ] Update **Current State** rows that changed
- [ ] Log any **Decisions Made** (prevents relitigating them next session)
- [ ] Move anything weird or broken into **Warnings / Gotchas**
- [ ] Commit Blueprint assets if any were created
- [ ] Push to GitLab

---

## Minimum viable update (brain fog edition)

If you can only do one thing, update **Next 3 Actions**.
That is the one piece of information that will save you next session.

---

## Git commands

Run from repo root: C:\Users\megan\Documents\lattice\

  git add -A
  git commit -m "session YYYY-MM-DD: brief description"
  git push

Binary .uasset files go through Git LFS automatically. That is expected and correct.

---

## Before closing Unreal

- Ctrl+S to save all
- Project Settings > Maps & Modes -- GameMode still BP_LatticeGameMode?
- BP_LatticePlayerCharacter Class Defaults -- input actions still assigned?
  (They clear on recompile. Easy to miss.)
