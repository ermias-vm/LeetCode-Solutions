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
  - **[Easy/](C++/Easy/)** - Easy difficulty problems
  - **[Medium/](C++/Medium/)** - Medium difficulty problems
  - **[Hard/](C++/Hard/)** - Hard difficulty problems
  - **[Makefile](C++/Makefile)** - C++-specific Makefile
- **[Java/](Java/)** - Java solutions
  - **[Easy/](Java/Easy/)** - Easy difficulty problems
  - **[Medium/](Java/Medium/)** - Medium difficulty problems
  - **[Hard/](Java/Hard/)** - Hard difficulty problems
  - **[Makefile](Java/Makefile)** - Java-specific Makefile
- **[ExpectedOutputs/](ExpectedOutputs/)** - Expected test outputs for verification
  - **[Easy/](ExpectedOutputs/Easy/)** - Expected outputs for easy problems
  - **[Medium/](ExpectedOutputs/Medium/)** - Expected outputs for medium problems
  - **[Hard/](ExpectedOutputs/Hard/)** - Expected outputs for hard problems

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

### Verification

| Command | Description |
|---------|-------------|
| `make verify all` | Verify all problems in C, C++, and Java |
| `make verify c` | Verify all C solutions |
| `make verify c++` | Verify all C++ solutions |
| `make verify java` | Verify all Java solutions |

### Utilities

| Command | Description |
|---------|-------------|
| `make summary` | Show table of all problems and solutions |
| `make find<N>` | Find the source file for problem N |
| `make find<N> c++` | Find problem N in C++ |
| `make format` | Format all source files |
| `make format c++` | Format only C++ files |
| `make clean_all` | Clean all compiled files |
| `make help` | Show all available commands |

---

## Output Verification

Each problem run automatically verifies against expected outputs stored in [ExpectedOutputs/](ExpectedOutputs/).

**Expected output format** (`ExpectedOutputs/<Difficulty>/<N>.txt`):
```
3
[0, 1]
[1, 2]
[0, 1]
```
First line: number of test cases. Following lines: expected outputs.

Solutions must print `Output: <result>` for each test case.

### Verification Results Table

When running `make verify all`:

| Symbol | Meaning |
|--------|---------|
| ✓ | All tests passed |
| Number | Number of failed tests |
| - | No solution or not tested |
| PASS | All languages passed |
| FAIL | At least one language failed |

---

## Adding a New Solution

1. Create the solution file: `<Language>/<Difficulty>/<N>-<ProblemName>.<ext>`
2. Include a test runner that prints `Output: <result>` for each test case
3. Add expected outputs to [ExpectedOutputs/](ExpectedOutputs/)`<Difficulty>/<N>.txt`
4. Run with `make <N> <language>` to verify

## File Naming Convention

- **Source files**: `<problem_number>-<ProblemName>.<extension>`
  - Example: `1-TwoSum.c`, `42-TrappingRainWater.cc`, `153-FindMinimumInRotatedSortedArray.java`
- **Expected outputs**: `<problem_number>.txt`
  - Example: `1.txt`, `42.txt`, `153.txt`
