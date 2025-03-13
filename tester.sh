#!/bin/bash

# Function to display usage
usage() {
    echo "Usage: $0 [-l] <exec1> <exec2> <test_cases_file> [args_file]"
    exit 1
}

# Check if the script has at least 3 arguments
long_output=false
if [ "$1" == "-l" ]; then
    long_output=true
    shift
fi

if [ "$#" -lt 3 ]; then
    usage
fi

exec1=$1
exec2=$2
test_file=$3
args_file=$4

# Check if executables and test file exist
if [ ! -x "$exec1" ] || [ ! -x "$exec2" ] || [ ! -f "$test_file" ]; then
    echo "Error: One or more files are missing or not executable."
    exit 1
fi

# Read optional arguments
args=""
if [ -n "$args_file" ] && [ -f "$args_file" ]; then
    args=$(cat "$args_file")
fi

# Read test cases separated by blank lines
test_cases=()
current_case=""
while IFS= read -r line || [[ -n "$line" ]]; do
    if [[ -z "$line" ]]; then
        if [[ -n "$current_case" ]]; then
            test_cases+=("$current_case")
            current_case=""
        fi
    else
        current_case+="$line
"
    fi
done < "$test_file"

# Add last test case if not empty
if [[ -n "$current_case" ]]; then
    test_cases+=("$current_case")
fi

# Run test cases and compare outputs
for ((i=0; i<${#test_cases[@]}; i++)); do
    test_input="${test_cases[$i]}"
    
    actual_output=$(echo -e "$test_input" | "$exec1" $args)
    expected_output=$(echo -e "$test_input" | "$exec2" $args)
    
    if [ "$actual_output" != "$expected_output" ]; then
        echo "Test Case $((i+1)) FAILED"
        if $long_output; then
            echo "Input:"
            echo -e "$test_input"
            echo "Actual Output:"
            echo "$actual_output"
            echo "Expected Output:"
            echo "$expected_output"
            echo "------------------------"
        fi
    else
        echo "Test Case $((i+1)) PASSED"
    fi
done
