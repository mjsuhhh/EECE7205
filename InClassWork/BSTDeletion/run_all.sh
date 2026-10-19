#!/bin/bash
# Compile and run every program in this folder (binaries go to bin/)
cd "$(dirname "$0")"
mkdir -p bin
for f in case1 case1_q2 case1_q3 case1_q4 \
         case2 case2_q2 case2_q3 case2_q4 \
         case3 case3_q2 case3_q3 case3_q4 case3_q4_unfixed \
         case4 case4_q1 case4_q3 case4_q4 \
         case5 case5_q2 case5_q3 case5_q4 bonus; do
    g++ -std=c++17 -Wall -o "bin/$f" "$f.cpp" || exit 1
    echo "===== $f ====="
    "./bin/$f"
    echo
done
