# EECE 7205 — Assignment #01 (In-Class Work): Sorting Algorithms

Seven C++ programs for the in-class sorting assignment (Bubble, Insertion, Selection, Quick, Merge and Heap Sort, plus one program that compares all six). The pseudocode, traces, analysis and written answers for every problem are in [SOLUTIONS.md](SOLUTIONS.md), and the technical report for submission is [Assignment01_Suh.pdf](Assignment01_Suh.pdf). This folder is separate from the ten-problem Assignment #01 files in the repository root.

## Quick start

```bash
cd InClassWork
./run_all.sh     # builds every program into bin/ and writes output/ProblemXX.txt
```

To build and run a single program:

```bash
g++ -std=c++17 -Wall -Wextra -o problem01 cpp/Assignment01_Problem01_Suh.cpp && ./problem01
g++ -std=c++17 -O2 -o problem07 cpp/Assignment01_Problem07_Suh.cpp && ./problem07   # -O2 for timing
```

## Files

| Path | Contents |
|---|---|
| `cpp/Assignment01_Problem01_Suh.cpp` | Bubble Sort with an early-exit flag: passes, comparisons, swaps, and a run on a sorted copy |
| `cpp/Assignment01_Problem02_Suh.cpp` | Insertion Sort: the key at every step, comparisons, shifts, and ascending/descending runs |
| `cpp/Assignment01_Problem03_Suh.cpp` | Selection Sort: the minimum and its index in every pass, comparisons, swaps |
| `cpp/Assignment01_Problem04_Suh.cpp` | Quick Sort (Lomuto, last-element pivot): first-partition trace, indented recursion tree, sorted-copy run |
| `cpp/Assignment01_Problem05_Suh.cpp` | Merge Sort: every split and merge, total and final-merge comparisons, sorted and reversed runs |
| `cpp/Assignment01_Problem06_Suh.cpp` | Heap Sort: heap after the build phase, heap and sorted parts of every pass, siftDown swaps |
| `cpp/Assignment01_Problem07_Suh.cpp` | All six sorts: comparison table, timing on random arrays, correctness check, almost sorted input |
| `SOLUTIONS.md` | Written solutions for all seven problems |
| `Assignment01_Suh.pdf` | Technical report: approach, pseudocode, code, output and written answers for every problem |
| `Assignment01_Suh.tex` | LaTeX source of the report; rebuild it from this folder with `tectonic Assignment01_Suh.tex` |
| `output/` | Output of every program from `./run_all.sh` (macOS, Apple clang 21) |
| `run_all.sh` | Builds and runs all seven programs; set `CXX` to use another compiler |

## Notes

- Every program follows the handout's design: `printArray(const int arr[], int n)` prints every array, no library sorting function is used, and the counters are passed by reference and printed in `main()`.
- All seven files compile without warnings under `-std=c++17 -Wall -Wextra -pedantic` with Apple clang 21 and with g++ on Linux, and Problems 1–6 print identical output on both.
- Problem 6 prints the heap part and the sorted part of each pass on two aligned lines, because `printArray` ends its line.
- Problem 7's timings depend on the machine. Its comparison counts do not, and neither does its random data: `mt19937` with a fixed seed produces the same values with every compiler.
