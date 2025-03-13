#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <your_executable> <reference_executable> <test_cases_file>"
    exit 1
fi

YOUR_EXEC="$1"
REF_EXEC="$2"
TEST_FILE="$3"

if [ ! -x "$YOUR_EXEC" ]; then
    echo "Error: $YOUR_EXEC is not an executable file."
    exit 1
fi

if [ ! -x "$REF_EXEC" ]; then
    echo "Error: $REF_EXEC is not an executable file."
    exit 1
fi

if [ ! -f "$TEST_FILE" ]; then
    echo "Error: Test file $TEST_FILE does not exist."
    exit 1
fi

TEST_COUNT=0
MISMATCH_COUNT=0

while IFS= read -r line; do
    if [[ -z "$line" ]]; then
        continue
    fi
    
    TEST_CASE+="$line
"
done < "$TEST_FILE"

echo "Running test case:"
echo -e "$TEST_CASE"

YOUR_OUTPUT=$(echo -e "$TEST_CASE" | "$YOUR_EXEC")
REF_OUTPUT=$(echo -e "$TEST_CASE" | "$REF_EXEC")

if [ "$YOUR_OUTPUT" != "$REF_OUTPUT" ]; then
    echo "Mismatch found!"
    echo "Your Output:"
    echo "$YOUR_OUTPUT"
    echo "Expected Output:"
    echo "$REF_OUTPUT"
    MISMATCH_COUNT=$((MISMATCH_COUNT + 1))
else
    echo "Test Passed."
fi

echo "------------------------------------"

echo "Total test cases run: 1"
echo "Mismatched cases: $MISMATCH_COUNT"

if [ "$MISMATCH_COUNT" -eq 0 ]; then
    echo "All test cases passed!"
else
    echo "Some test cases failed."
fi
