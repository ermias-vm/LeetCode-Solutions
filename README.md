# LeetCode Solutions

A collection of [LeetCode](https://leetcode.com/problemset/) problem solutions in **C**, **C++**, and **Java**, organized by difficulty level with automatic output verification.

## Directory Structure

- **[Makefile](Makefile)** - Root Makefile (main entry point)
- **[verify_output.sh](verify_output.sh)** - Output verification script
- **[C/](C/)** - C solutions
  - **[Easy/](C/Easy/)** - Easy difficulty problems
  - **[Medium/](C/Medium/)** - Medium difficulty problems
  - **[Hard/](C/Hard/)** - Hard difficulty problems
  - **[Makefile](C/Makefile)** - C-specific Makefile
- **[C++/](C++/)** - C++ solutions
  - **[Easy/](C++/Easy/)**
  - **[Medium/](C++/Medium/)**
  - **[Hard/](C++/Hard/)**
  - **[Makefile](C++/Makefile)** - C++-specific Makefile
- **[Java/](Java/)** - Java solutions
  - **[Easy/](Java/Easy/)**
  - **[Medium/](Java/Medium/)**
  - **[Hard/](Java/Hard/)**
  - **[Makefile](Java/Makefile)** - Java-specific Makefile
- **[Results/](Results/)** - Expected test outputs for verification
  - **[Easy/](Results/Easy/)** 
  - **[Medium/](Results/Medium/)**
  - **[Hard/](Results/Hard/)**
- **[Templates/](Templates/)** - Solution templates for new problems
  - **[template.c](Templates/template.c)** - C template
  - **[template.cc](Templates/template.cc)** - C++ template
  - **[template.java](Templates/template.java)** - Java template
- **[Out/]** - Generated output folder (gitignored)
  - **logs/** - Verification results with timestamps
  - **tmp/** - Temporary output files
  - **Solutions_summary.txt** - Summary table

---

## Quick Start

Run any problem directly from the project root:

```bash
make 1            # Run problem 1 in default language (C)
make 1 c++        # Run problem 1 in C++
make 1 java       # Run problem 1 in Java
```

This command compiles, runs, verifies the output, and cleans up automatically:

```
Running problem 1 in C (c)...

Compiling ./Easy/1-TwoSum.c to ./Easy/1-TwoSum.x
Running file ./Easy/1-TwoSum.x
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]

Input: nums = [3, 2, 4], target = 6
Output: [1, 2]

Input: nums = [3, 3], target = 6
Output: [0, 1]


Expected Outputs: [0, 1], [1, 2], [0, 1]
Result: Passed (3 test(s))
Deleting ./Easy/1-TwoSum.x
```

---

## Commands Reference

### Running Problems (Main Commands)

| Command | Description |
|---------|-------------|
| `make <N>` | Run problem N (compile, execute, verify, clean) |
| `make <N> c` | Run problem N in C |
| `make <N> c++` | Run problem N in C++ |
| `make <N> java` | Run problem N in Java |

### Individual Steps

| Command | Description |
|---------|-------------|
| `make compile<N>` | Compile problem N only |
| `make run<N>` | Run problem N only |
| `make clean<N>` | Clean compiled files for problem N |

### Verification & Summary

| Command | Description |
|---------|-------------|
| `make verify all` | Verify all problems (C, C++, Java) → `Out/logs/` |
| `make verify c` | Verify all C solutions → `Out/logs/` |
| `make verify c++` | Verify all C++ solutions → `Out/logs/` |
| `make verify java` | Verify all Java solutions → `Out/logs/` |
| `make summary` | Show & save summary → `Out/Solutions_summary.txt` |

### Utilities

| Command | Description |
|---------|-------------|
| `make find<N>` | Find the source file for problem N |
| `make find<N> c++` | Find problem N in C++ |
| `make format` | Format all source files |
| `make format c++` | Format only C++ files |
| `make clean_all` | Clean all compiled files |
| `make clean out` | Delete `Out/` folder (with confirmation) |
| `make help` | Show all available commands |

---

## Output Verification

Each problem run automatically verifies against expected outputs stored in [Results/](Results/).

**Expected output format** (`Results/<Difficulty>/<N>.txt`):
```
3
[0, 1]
[1, 2]
[0, 1]
```
First line: number of test cases. Following lines: expected outputs.

Solutions must print `Output: <result>` for each test case.

### Verification Results

Logs are saved to `Out/logs/` with timestamps:
- `All_TestResults_PASS_20260118_153042.txt`
- `C++_TestResults_FAIL_20260118_153042.txt`

| Value | Meaning |
|-------|---------|
| 0 | All tests passed (0 errors) |
| N | Number of failed tests |
| - | No solution or not tested |
| PASS | All tested problems passed |
| FAIL | At least one test failed |

---

## Adding a New Solution

1. Create the solution file: `<Language>/<Difficulty>/<N>-<ProblemName>.<ext>`
2. Include a test runner that prints `Output: <result>` for each test case
3. Add expected outputs to [Results/](Results/)`<Difficulty>/<N>.txt`
4. Run with `make <N> <language>` to verify

## File Naming Convention

- **Source files**: `<problem_number>-<ProblemName>.<extension>`
  - Example: `1-TwoSum.c`, `42-TrappingRainWater.cc`, `153-FindMinimumInRotatedSortedArray.java`
- **Expected outputs**: `<problem_number>.txt`
  - Example: `1.txt`, `42.txt`, `153.txt`
