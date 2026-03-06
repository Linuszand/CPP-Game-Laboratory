# Battleships Buggy Lab — Answers

## Team

- Team name: Team 01
- Partner A: Linus Zackrisson Andersson
- Partner B: Shaun Milligan

---

## 1) Requirement → Code Map (spec verification)

Fill this table by reading `games/battleships/specification.md` and mapping requirements to code.

| Requirement (from specification.md)            | Pass/Fail/Unsure | Code location (file + class/function)                                | Notes (what it does)         |
| ---------------------------------------------- | ---------------- | -------------------------------------------------------------------- | ---------------------------- |
| Example: Turns alternate after each valid shot |                  | `battleships_buggy/src/core/Game.cpp` → `Game::AdvanceTurn`     | flips current player index   |
| Example: Tracking board records shots          |                  | `battleships_buggy/src/core/Game.cpp` → `Game::ShootAtOpponent` | updates `Player::tracking` |

Add rows for all major requirements you verify.

---

## 2) Spec verification summary

Write Pass/Fail/Unsure for each area and explain *how you verified it* (test steps or observation).

- Setup phase:
- Placement rules:
- Input commands:
- Shot resolution:
- Tracking board:
- Win condition:

---

## 3) Bugs found (at least 6 total)

You must list at least:

- 3 functional bugs (incorrect behavior vs spec)
- 3 robustness issues (bad input handling, silent failures, crashes, etc.)

### Bug 1

- Symptom: Game starts after Player1 has placed all of his/her ships.
- Steps to reproduce (exact inputs): Place all of player1's ships down in the game area.
- Expected (spec): For the current players turn to change to Player2, not start the game.
- Actual: It starts the game, and if Player1 shoots, the game is over instantly, because player2 has no ships placed.
- Suspected root cause (file/function):  Wrong placement of function calls.
- Fix approach: Change theo rder of function calls, game.NectPlayerDuringSetup(); should be before game.FinishSetupIfReady();

### Bug 2

- Symptom: Placing ships gave poor feedback
- Steps to reproduce (exact inputs): Place out of bounds or over other ship
- Expected (spec): Descriptive error message
- Actual: Non descriptive generic error message
- Suspected root cause (file/function): place ship returned bool not enum
- Fix approach: have place ship return PlaceResult Enum

### Bug 3

- Symptom:
- Steps to reproduce (exact inputs):
- Expected (spec):
- Actual:
- Suspected root cause (file/function):
- Fix approach:

### Bug 4

- Symptom:
- Steps to reproduce (exact inputs):
- Expected (spec):
- Actual:
- Suspected root cause (file/function):
- Fix approach:

### Bug 5

- Symptom:
- Steps to reproduce (exact inputs):
- Expected (spec):
- Actual:
- Suspected root cause (file/function):
- Fix approach:

### Bug 6

- Symptom:
- Steps to reproduce (exact inputs):
- Expected (spec):
- Actual:
- Suspected root cause (file/function):
- Fix approach:

(Add more if you find more.)

---

## 4) Code smells found (at least 5)

A “smell” is not necessarily a bug, but a design/implementation choice that increases risk or cost.

### Smell 1

- What (where in code):
- Why risky:
- Better approach (short plan):

### Smell 2

- What (where in code):
- Why risky:
- Better approach (short plan):

### Smell 3

- What (where in code):
- Why risky:
- Better approach (short plan):

### Smell 4

- What (where in code):
- Why risky:
- Better approach (short plan):

### Smell 5

- What (where in code):
- Why risky:
- Better approach (short plan):

---

## 5) Good patterns found (at least 4)

Find at least 4 things the code does reasonably well.

### Good thing 1

- Where:
- Why good:
- How to reuse:

### Good thing 2

- Where:
- Why good:
- How to reuse:

### Good thing 3

- Where:
- Why good:
- How to reuse:

### Good thing 4

- Where:
- Why good:
- How to reuse:

---

## 6) Team bug-fix PR (pair programming)

- Branch name:
- PR link:
- Bugs fixed (list):
- Tests added/updated:
- How you verified the fixes:
- What you learned:

---

## 7) Team feature PR (pair programming)

- Feature implemented (from spec’s “Explicit Missing Features”):
- Branch name:
- PR link:

Mini-spec (write BEFORE coding):

- Behavior:
- Edge cases:
- How to verify (test or manual steps):

Verification performed:

- Tests/manual steps used:
- Result:

---

## 8) Individual feature PRs

### Partner A

- Feature:
- Branch:
- PR link:

Mini-spec:

- Behavior:
- Edge cases:
- How to verify:

Verification performed:

- Tests/manual steps used:
- Result:

### Partner B

- Feature:
- Branch:
- PR link:

Mini-spec:

- Behavior:
- Edge cases:
- How to verify:

Verification performed:

- Tests/manual steps used:
- Result:

---

## 9) Manual test script (if needed)

If you could not write tests for some behavior, write a reproducible manual test script.

Example format:

1) Start game
2) Place ships for both players with valid placements
3) Player 1 shoots A1 → expect: Miss/Hit/Sunk
4) Player 1 shoots A1 again → expect: AlreadyTried and turn should NOT change
