# Word Search Puzzle Solver

A C++ word search solver that benchmarks different combinations of grid and dictionary data structures to compare their performance. The program searches an N×N letter grid in all 8 directions and matches words against a dictionary, running every combination of grid and dictionary implementation and writing results to separate output files.

---

## Overview

The solver is built around a deliberate design experiment: rather than picking one data structure, it implements two grid representations and three dictionary representations, then runs all six combinations. Each combination's output file records matched/unmatched words, grid and dictionary visit counts, timing, and memory usage — making it straightforward to compare the trade-offs between implementations.

---

## Repository Structure

```
WordSearch/
├── Main.cpp                        # Entry point — runs all 6 combinations
├── WordSearch.h / .cpp             # Orchestrator class
├── SimpleGrid.h / .cpp             # 2D vector grid
├── AdvancedGrid.h / .cpp           # Doubly-linked node grid
├── SimpleDictionary.h / .cpp       # Sorted vector + binary search
├── AdvancedDictionary.h / .cpp     # Trie
├── HashDictionary.h / .cpp         # Hash map (words + all prefixes)
├── Solver.h / .cpp                 # (reserved)
├── Metrics.h / .cpp                # (reserved)
├── Timer.h / .cpp                  # (reserved)
├── grid.txt                        # Input puzzle grid
├── dictionary.txt                  # Input word list
├── simple_puzzle_simple_dictionary.txt
├── simple_puzzle_advanced_dictionary.txt
├── simple_puzzle_hash_dictionary.txt
├── advanced_puzzle_simple_dictionary.txt
├── advanced_puzzle_advanced_dictionary.txt
├── advanced_puzzle_hash_dictionary.txt
├── WordSearch.vcxproj              # Visual Studio project file
└── WordSearch.sln                  # Visual Studio solution file
```

---

## Input Format

**`grid.txt`** — first line is the integer grid size N, followed by N×N space-separated characters:
```
9
V G G D C M E N Y
Y A J F O C C I R
...
```

**`dictionary.txt`** — one word per line, uppercase:
```
COURAGE
DELIVERY
DEVICE
...
```

---

## Data Structures

### Grid Representations

| | SimpleGrid | AdvancedGrid |
|---|---|---|
| **Structure** | `std::vector<std::vector<char>>` | Flat array of `Cell` nodes with 8 directional pointers |
| **Memory** | N² × sizeof(char) | N² × sizeof(Cell) |
| **Traversal** | Index arithmetic | Pointer chasing |
| **Advantage** | Minimal memory | No bounds-checking during traversal |

`AdvancedGrid` allocates all cells in a single flat array and links each cell to its up/down/left/right/diagonal neighbours at load time. During solving, the algorithm simply follows pointers instead of computing `(x+dx, y+dy)` and bounds-checking each step.

### Dictionary Representations

| | SimpleDictionary | AdvancedDictionary | HashDictionary |
|---|---|---|---|
| **Structure** | Sorted `std::vector<std::string>` | Trie | `std::unordered_map<string, bool>` |
| **Prefix check** | `lower_bound` comparison | Trie walk | Hash lookup (all prefixes pre-stored) |
| **Word check** | `binary_search` | Trie node flag | Hash lookup |
| **Memory** | Low | Medium (one node per unique prefix character) | High (stores every prefix explicitly) |
| **Speed** | O(log n) per lookup | O(k) per character | O(1) amortised |

`HashDictionary` pre-computes and stores every prefix of every word at load time, enabling O(1) combined prefix+word lookup during solving.

---

## Solving Algorithm

The solver scans every cell in the grid and, from each cell, extends strings in all 8 directions (horizontal, vertical, and both diagonals). Early termination is applied as soon as a partial string is no longer a valid prefix in the dictionary — avoiding full exhaustive search.

- Strings shorter than the dictionary's shortest word are skipped.
- Strings longer than the dictionary's longest word are not extended.
- Duplicate words (found via multiple paths) are deduplicated using an `unordered_set`.

Each found word is recorded along with its starting grid position (column, row).

---

## Output Format

Each of the six output files follows the same structure:

```
Number of words matched: 6

Words matched in grid:
0 0 VARIATION
4 0 COURAGE
...

Words unmatched in grid:
EMPLOYEE

Number of grid cells visited: 1259
Number of dictionary entries visited: 234

Time to populate grid: 0.010167
Time to populate dictionary: 0.007256
Time to solve puzzle: 0.000368

Size of the grid data structure: 81
Size of the dictionary data structure: 385
```

Times are in seconds. Sizes are in bytes.

---

## Building

The project targets Windows with the included Visual Studio solution (`WordSearch.sln`). Open the solution in Visual Studio 2019 or later and build in Release mode for meaningful performance benchmarks.

No external dependencies — the project uses only the C++ standard library.

---

## Usage

1. Place `grid.txt` and `dictionary.txt` in the working directory (the project sets this to the `WordSearch/` folder by default).
2. Build and run the executable.
3. Six output `.txt` files are written to the working directory, one per grid/dictionary combination.

---

## Example Results (9×9 grid, 7-word dictionary)

The included sample grid and dictionary find **6 of 7 words** (EMPLOYEE is not present in the grid):

```
VARIATION   — found at (0, 0)
COURAGE     — found at (4, 0)
ECONOMICS   — found at (6, 0)
THEORY      — found at (8, 5)
DEVICE      — found at (5, 7)
DELIVERY    — found at (0, 8)
```

The Trie (AdvancedDictionary) reduces grid cells visited from **1,259** (SimpleDictionary) to **316**, demonstrating the benefit of character-level prefix pruning over sorted-vector binary search.
