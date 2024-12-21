#!/bin/bash

# Set output log files
DEBUG_LOG="push_swap_100_debug.log"
RESULT_LOG="push_swap_100_results.log"

# Cleanup old logs
rm -f $DEBUG_LOG $RESULT_LOG

echo "Starting 100-element push_swap test..." | tee -a $RESULT_LOG

# Generate random 100 elements
ARG=$(ruby -e "puts (1..100).to_a.shuffle.join(' ')")
echo "Generated Input: $ARG" | tee -a $DEBUG_LOG

# Run push_swap and checker_linux
echo "Running push_swap and checker_linux..." | tee -a $DEBUG_LOG
OPERATIONS=$(./push_swap $ARG 2>>$DEBUG_LOG | tee temp_ops.log | wc -l)
./push_swap $ARG 2>>$DEBUG_LOG | ./checker_linux $ARG >>$DEBUG_LOG 2>&1

# Analyze Results
RESULT=$(tail -1 $DEBUG_LOG)
if [[ $RESULT == "OK" ]]; then
    echo "Test Passed: Output is correct!" | tee -a $RESULT_LOG
else
    echo "Test Failed: Output is incorrect!" | tee -a $RESULT_LOG
fi

# Action Count
echo "Total operations: $OPERATIONS" | tee -a $RESULT_LOG

# Save operations
echo "Operations performed:" | tee -a $RESULT_LOG
cat temp_ops.log | tee -a $RESULT_LOG

# Clean up temporary file
rm -f temp_ops.log

# Final summary
echo "Test complete. Results logged in $RESULT_LOG and debug details in $DEBUG_LOG."
