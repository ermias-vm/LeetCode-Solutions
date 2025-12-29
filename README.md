# LeetCode Solutions

Welcome to the **LeetCode Solutions** repository! This is a comprehensive collection of solutions and explanations for problems found on [LeetCode](https://leetcode.com/problemset/).

## What's Inside

- **Solutions**: Code solutions for LeetCode problems in **C**, **C++**, **Java**, and **Python**.
- **Explanations**: Brief insights into the strategy and thought process for each solution.
- **Difficulty Levels**: Solutions are categorized by their difficulty level - Easy, Medium, and Hard within each language folder.
- **Output Verification**: Automatic verification of solution outputs against expected LeetCode test cases.

## Directory Structure

The repository is organized by programming language, and then by difficulty:

```
LeetCode-Solutions/
├── C/
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── C++/
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── Java/
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── Python/
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── ExpectedOutputs/
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── verify_output.sh
└── README.md
```


## How to Use the Makefiles

Each language directory (`C/`, `C++/`, `Java/`, `Python/`) contains a `Makefile` that automates compiling, running, cleaning, and finding solutions. All commands below work in all four languages (except where noted).

### 1. Navigate to the Language Directory
Before using any `make` commands, ensure you are in the respective language directory:
```bash
cd C         # For C solutions
# OR
cd C++       # For C++ solutions
# OR
cd Java      # For Java solutions
# OR
cd Python    # For Python solutions
```

### 2. Find a Problem File
Quickly locate the file for a specific problem number:
```bash
make find<problem_number>
```
Example:
```bash
make find1
```
This prints the path to the file for problem 1 (e.g., `./Easy/1-TwoSum.java`).

### 3. Compile a Problem (C/C++/Java only)
Compile the solution file for the given problem number:
```bash
make compile<problem_number>
```
Example:
```bash
make compile20  # Finds and compiles 20-ProblemName.c, 20-ProblemName.cc, or 20-ProblemName.java
```
- For C/C++, this creates an executable (e.g., `20-ProblemName.x`).
- For Java, this creates `.class` files.
- For Python, this step is not needed.

### 4. Run a Problem
Run the solution for the given problem number:
```bash
make run<problem_number>
```
Example:
```bash
make run20
```
- For C/C++ and Java, this executes the compiled solution (compiles first if needed).
- For Python, this executes the script directly.

### 5. Compile & Run (or Just Run for Python)
**The most convenient command:**

```bash
make <problem_number>
```
**Example:**
```bash
make 20
```
- **For C/C++ and Java:** Compiles (if needed) and then runs the solution. **After execution, the compiled executable (`.x`) or `.class` files are automatically deleted to keep the directory clean.**
- **For Python:** Runs the script (no compilation or cleanup needed).

### 6. Clean Compiled Files
- **Clean a specific problem:**
  ```bash
  make clean<problem_number>
  ```
  Removes the compiled files (e.g., `.x` for C/C++, `.class` for Java) for that problem.
- **Clean all compiled files:**
  ```bash
  make clean_all
  ```
  Removes all compiled files in the language directory.

---

## Output Verification System

Each time you run a problem with `make run<number>` or `make <number>`, the output is automatically verified against the expected LeetCode test case outputs.

### How it Works

1. **Expected Outputs**: The `ExpectedOutputs/` folder contains `.txt` files for each problem, organized by difficulty (Easy, Medium, Hard).
2. **Format**: Each expected output file has the number of test cases on the first line, followed by one expected output per line.
3. **Verification**: When you run a problem, the script captures lines containing "Output:" and compares them against the expected values.

### Example

For problem 1 (Two Sum), the expected output file `ExpectedOutputs/Easy/1.txt` contains:
```
3
[0, 1]
[1, 2]
[0, 1]
```

When you run `make 1`, the verification shows:
```
PASSED: Output '[0, 1]' matches expected.
Expected Outputs: [0, 1], [1, 2], [0, 1]
```

### Adding Expected Outputs

To add verification for a new problem:
1. Create a file `ExpectedOutputs/<Difficulty>/<problem_number>.txt`
2. First line: number of expected outputs
3. Following lines: one expected output per line (matching the format your solution prints)

---

## Summary Table
| Command Example         | Description                                      |
|------------------------|--------------------------------------------------|
| `make find1`           | Find the file for problem 1                      |
| `make compile1`        | Compile problem 1 (C/C++/Java only)              |
| `make run1`            | Run problem 1                                    |
| `make 1`               | Compile (if needed) and run problem 1            |
| `make clean1`          | Remove compiled files for problem 1              |
| `make clean_all`       | Remove all compiled files in the directory       |

---

## Tips
- Always use the correct language directory before running `make` commands.
- The `find` command is useful to quickly locate where a problem's solution is stored.
- Use `clean` and `clean_all` to keep your workspace tidy, especially after compiling or running multiple problems.
