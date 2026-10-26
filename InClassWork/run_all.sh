#!/usr/bin/env bash
# Builds every problem into bin/ and saves each program's output in output/.
# Usage, from the InClassWork folder:   ./run_all.sh
# A different compiler can be chosen with, e.g.,   CXX=clang++ ./run_all.sh
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p bin output
CXX="${CXX:-g++}"

for p in 01 02 03 04 05 06 07; do
    src="cpp/Assignment01_Problem${p}_Suh.cpp"
    flags="-std=c++17 -Wall -Wextra -pedantic"
    if [ "$p" = "07" ]; then flags="$flags -O2"; fi   # optimized build for the timings
    "$CXX" $flags -o "bin/problem$p" "$src"
    "./bin/problem$p" > "output/Problem$p.txt"
    echo "Problem $p: built and ran -> output/Problem$p.txt"
done
