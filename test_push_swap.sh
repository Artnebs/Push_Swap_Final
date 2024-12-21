#!/bin/bash

# Redirect all output (stdout and stderr) to a log file
LOGFILE="push_swap_test_results.log"
exec >"$LOGFILE" 2>&1

# Timestamp for the log
echo "Test Run Timestamp: $(date)"
echo "----------------------------------------"

# Basic tests
echo "Basic Tests"
./push_swap 1 2 3 | ./checker_linux 1 2 3
./push_swap 3 2 1 | ./checker_linux 3 2 1
./push_swap 2 1 | ./checker_linux 2 1
./push_swap 5 4 3 2 1 | ./checker_linux 5 4 3 2 1
echo "----------------------------------------"

# Edge cases
echo "Edge Cases"
./push_swap | ./checker_linux
./push_swap 42 | ./checker_linux 42
./push_swap 1 2 3 2 | ./checker_linux 1 2 3 2
./push_swap 2147483648 | ./checker_linux 2147483648
./push_swap -2147483649 | ./checker_linux -2147483649
./push_swap 1 two 3 | ./checker_linux 1 two 3
echo "----------------------------------------"

# Randomized small tests
echo "Randomized Small Tests"
for i in {1..5}; do
    ARG=$(ruby -e "puts (1..10).to_a.shuffle.join(' ')")
    echo "Test $i with ARG: $ARG"
    ./push_swap $ARG | ./checker_linux $ARG
    echo "----------------------------------------"
done

# Performance tests
echo "Performance Tests"
ARG=$(ruby -e "puts (1..100).to_a.shuffle.join(' ')")
echo "Performance Test 100 Elements with ARG: $ARG"
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker_linux $ARG
echo "----------------------------------------"

ARG=$(ruby -e "puts (1..500).to_a.shuffle.join(' ')")
echo "Performance Test 500 Elements with ARG: $ARG"
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker_linux $ARG
echo "----------------------------------------"

# Stress tests
echo "Stress Tests"
echo "Reverse 100:"
./push_swap $(seq 100 -1 1) | ./checker_linux $(seq 100 -1 1)
echo "----------------------------------------"

echo "Reverse 500:"
./push_swap $(seq 500 -1 1) | ./checker_linux $(seq 500 -1 1)
echo "----------------------------------------"

echo "Alternating High-Low (1 to 99 and 100 to 2):"
./push_swap $(seq 1 2 99) $(seq 100 -2 2) | ./checker_linux $(seq 1 2 99) $(seq 100 -2 2)
echo "----------------------------------------"

echo "All Negative Numbers (-1 to -100):"
./push_swap $(seq -1 -1 -100) | ./checker_linux $(seq -1 -1 -100)
echo "----------------------------------------"

# Indicate test completion
echo "----------------------------------------"
echo "Test Run Completed. Results logged in $LOGFILE"
