# Battleships — Console Game Specification (Lab Day 4)

**Lab focus:** Review • Debug • Improve • Extend  
**Repository:** CPP-Game-Laboratory  
**Game:** Battleships  
**Audience:** Students working in pairs  
**Version:** 1.0

---

## Purpose

A complete specification to verify the **buggy starter code** against, then fix/refactor and implement missing features.

---

## 1. Overview

Battleships is a **turn-based, two-player, hot-seat** console game. Each player places a fleet of ships on a hidden grid. Players then take turns firing shots at coordinates on the opponent’s grid. The first player to sink all opponent ships wins.

### 1.1 Definitions

| Term | Meaning |
|---|---|
| Grid | A 10×10 board addressed by columns **A–J** and rows **1–10**. |
| Fleet | The set of ships each player places during setup. |
| Tracking board | A player’s record of shots taken at the opponent. |
| Sunk | All segments/cells of a ship have been hit. |

---

## 2. Game Flow

### 2.1 States

- **Main menu** *(optional in buggy version)*
- **Setup** (ship placement)
- **Playing** (turns)
- **Game Over** (winner + summary)

### 2.2 Setup Phase

Players place ships on their own grid.

**Requirements:**
- Placement must be validated (**bounds + overlap**).
- After **Player 1** finishes placement, the game must switch to **Player 2** placement (hot-seat).
- The **Playing** phase starts **only when BOTH players** have placed the full fleet.

### 2.3 Playing Phase

On a turn, the current player chooses a target coordinate on the opponent’s grid.

**Requirements:**
- The game reports the shot result (**Miss/Hit/Sunk/AlreadyTried/Invalid**) and updates the tracking board.
- Turns alternate until one player has sunk all opponent ships.

---

## 3. Board, Coordinates, and Fleet

### 3.1 Coordinate System

Coordinates use column letters **A–J** (left → right) and row numbers **1–10** (top → bottom).

Examples:
- **A1** is the top-left cell.
- **J10** is the bottom-right cell.

### 3.2 Fleet Composition

Each player has the following ships (length in cells):

| Ship | Length |
|---|---:|
| Destroyer | 2 |
| Submarine | 3 |
| Cruiser | 3 |
| Battleship | 4 |
| Carrier | 5 |

### 3.3 Placement Rules

- Ships may be placed **horizontally** or **vertically**.
- Ships must be **fully within** the grid.
- Ships must **not overlap**.
- *(Optional stretch)* Ships must **not touch** (one-cell buffer).

---

## 4. Input and Commands

The game is console-based. Input handling must be robust:

- Reject invalid commands
- Re-prompt without crashing
- Never accept out-of-range coordinates **silently**

### 4.1 Required Commands

| Command | Behavior |
|---|---|
| `help` | Show available commands and examples. |
| `quit` | Quit the program immediately. |
| `shoot <coord>` | Fire at the opponent (e.g. `shoot B7`). |
| `<coord>` | Shorthand for shooting (e.g. `B7`). |

### 4.2 Setup Input

During setup, each ship placement must collect:
- **Start coordinate** (e.g. `A1`)
- **Orientation** (`H`/`V`)

If placement fails, the program must display an informative error:
- **OutOfBounds** vs **Overlap**

---

## 5. Shot Resolution

A shot must produce **exactly one** of the following results:

| Result | Rules |
|---|---|
| **Invalid** | Coordinate is outside the grid or command is malformed; **do not change turn**. |
| **AlreadyTried** | Cell was previously targeted; **do not change turn**. |
| **Miss** | Target cell contains no ship; mark miss and **end turn**. |
| **Hit** | Target cell contains a ship segment; mark hit and **end turn**. |
| **Sunk** | This hit completes a ship; mark hit + announce sunk; **end turn**. |

---

## 6. Win Condition

A player wins immediately when **all ships in the opponent’s fleet are sunk**. The program must announce the winner and show a **Game Over** screen.

---

## 7. Acceptance Criteria Checklist

Teams must verify the buggy code against these criteria, mark Pass/Fail, and create fixes in branches.

| Criterion | Type | Status (Pass/Fail) |
|---|---|--------------------|
| Setup starts with Player 1 and switches to Player 2 after Player 1 completes placement. | Functional | Fail               |
| Playing starts only after BOTH players placed the full fleet. | Functional | Fail               |
| Placement rejects overlap and out-of-bounds with correct error reason. | Correctness | Fail               |
| Shooting the same coordinate twice returns AlreadyTried and does not change turn. | Correctness | Fail               |
| Tracking board shows hits and misses correctly. | Correctness | Fail               |
| Win condition triggers only when opponent fleet is sunk. | Correctness |                    |
| Input handling never crashes on malformed input. | Robustness |                    |

---

## 8. Explicit Missing Features to Implement

These are intentionally missing or incorrect in the buggy starter code. Implement them **after** bug fixes:

1. **AlreadyTried**  
   Shooting a previously targeted cell must return `AlreadyTried` and **not consume the turn**.

2. **Accurate PlaceResult**  
   Placement must return `OutOfBounds` vs `Overlap` correctly.

3. **Correct tracking board**  
   Tracking board must mark hits as `Hit` (not `Ship`) and remain consistent.

---

## 9. Stretch Goals

- Add a main menu with **Play / Help / Quit**.
- Add random fleet placement with an optional RNG seed for reproducible games.
- Add an end-of-game summary (turns, hits, misses, accuracy).
- Add a simple unit test suite that covers overlap, bounds, and shot results.

---

## 10. Notes for Students

Work in pairs with short-lived branches and small PRs. Start from the specification and build an acceptance checklist. When a requirement is ambiguous, agree on an interpretation, document it, and implement consistently.