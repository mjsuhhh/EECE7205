#!/usr/bin/env bash
#=============================================================================
# EECE 7205 - Assignment #01 | MyungJin Suh
# Builds and runs the test suite. Exits 0 only if everything passes.
#=============================================================================
set -u
cd "$(dirname "$0")"

CXX=${CXX:-g++}
FLAGS="-std=c++17 -O2 -Wall -Wextra -Wno-unused-function"

echo "============================================================"
echo "  Building"
echo "============================================================"
printf "  %-18s " "test_solutions"
if $CXX $FLAGS -o test_solutions test_solutions.cpp 2> /tmp/test_build.log; then
    echo "compiled (no warnings)"
else
    echo "BUILD FAILED"
    cat /tmp/test_build.log
    exit 1
fi

echo
./test_solutions
status=$?

echo
echo "============================================================"
if [ $status -eq 0 ]; then
    echo "  ALL TESTS PASSED"
else
    echo "  SOME TESTS FAILED"
fi
echo "============================================================"
exit $status
