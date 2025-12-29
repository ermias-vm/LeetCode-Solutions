#!/bin/bash
# verify_output.sh - Verify program output against expected results
# Usage: verify_output.sh <problem_number> <actual_output_file> <difficulty>

PROBLEM_NUM=$1
OUTPUT_FILE=$2
DIFFICULTY=$3
SCRIPT_DIR="$(dirname "$0")"
EXPECTED_DIR="$SCRIPT_DIR/ExpectedOutputs/$DIFFICULTY"
EXPECTED_FILE="$EXPECTED_DIR/$PROBLEM_NUM.txt"

# Check if expected file exists
if [ ! -f "$EXPECTED_FILE" ]; then
    echo ""
    echo "Expected output file not found: ExpectedOutputs/$DIFFICULTY/$PROBLEM_NUM.txt"
    echo "Skipping verification."
    exit 0
fi

# Read number of test cases from first line
NUM_TESTS=$(head -n 1 "$EXPECTED_FILE")

# Extract Output lines from actual output (lines starting with "Output:")
OUTPUTS=$(grep "^Output:" "$OUTPUT_FILE" 2>/dev/null | sed 's/^Output: //')

if [ -z "$OUTPUTS" ]; then
    echo ""
    echo "No 'Output:' lines found in program output."
    echo "Make sure your solution prints 'Output: <result>' for verification."
    exit 0
fi

# Compare each output
PASSED=0
FAILED=0
MISMATCH_DETAILS=""

i=1
while IFS= read -r actual_output; do
    # Get expected output (line i+1 because first line is count)
    expected_output=$(sed -n "$((i+1))p" "$EXPECTED_FILE")
    
    if [ "$actual_output" = "$expected_output" ]; then
        PASSED=$((PASSED + 1))
    else
        FAILED=$((FAILED + 1))
        MISMATCH_DETAILS="$MISMATCH_DETAILS\n  Test $i: Expected '$expected_output', got '$actual_output'"
    fi
    i=$((i + 1))
done <<< "$OUTPUTS"

# Build expected outputs string
EXPECTED_OUTPUTS=""
for ((j=2; j<=NUM_TESTS+1; j++)); do
    exp=$(sed -n "${j}p" "$EXPECTED_FILE")
    if [ -n "$EXPECTED_OUTPUTS" ]; then
        EXPECTED_OUTPUTS="$EXPECTED_OUTPUTS, $exp"
    else
        EXPECTED_OUTPUTS="$exp"
    fi
done

echo ""
echo "Expected Outputs: $EXPECTED_OUTPUTS"
if [ $FAILED -eq 0 ]; then
    echo "Result: Passed ($PASSED test(s))"
else
    echo "Result: Failed ($FAILED mismatch(es) found)"
    printf "$MISMATCH_DETAILS\n"
fi
