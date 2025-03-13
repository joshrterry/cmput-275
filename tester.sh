#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "Usage: $0 <your_executable> <reference_executable> <test_cases_file> [-l]"
    exit 1
fi

LONG_OUTPUT=false
if [ "$#" -eq 4 ] && [ "$4" == "-l" ]; then
    LONG_OUTPUT=true
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

while IFS= read -r line || [ -n "$line" ]; do
    TEST_COUNT=$((TEST_COUNT + 1))
    
    echo "Test Case #$TEST_COUNT: $line"
    
    YOUR_OUTPUT=$(echo "$line" | "$YOUR_EXEC")
    REF_OUTPUT=$(echo "$line" | "$REF_EXEC")
    
    if [ "$YOUR_OUTPUT" != "$REF_OUTPUT" ]; then
        echo "Mismatch found!"
        if [ "$LONG_OUTPUT" = true ]; then
            echo "Your Output:"
            echo "$YOUR_OUTPUT"
            echo "Expected Output:"
            echo "$REF_OUTPUT"
        else
            echo "Your Output: $(echo "$YOUR_OUTPUT" | head -n 1) ... (truncated)"
            echo "Expected Output: $(echo "$REF_OUTPUT" | head -n 1) ... (truncated)"
        fi
        MISMATCH_COUNT=$((MISMATCH_COUNT + 1))
    else
        echo "Test Passed."
    fi
    
    echo "------------------------------------"
done < "$TEST_FILE"

echo "Total test cases run: $TEST_COUNT"
echo "Mismatched cases: $MISMATCH_COUNT"

if [ "$MISMATCH_COUNT" -eq 0 ]; then
    echo "All test cases passed!"
else
    echo "Some test cases failed."
fi
