# Tests — EECE 7205 Assignment #01

Automated tests for the solutions in `../cpp/Assignment01_Suh.cpp`.

## Run

```bash
cd test
./run_tests.sh
```

Exit code `0` means everything passed.

```bash
./test_solutions 3      # run only Problem 3
```

## Coverage

`test_solutions.cpp` — 3 cases per problem, 30 total: the provided example,
one additional case, and one edge case. Each prints the problem, input and
output.

```
 PROBLEM 1: Merge Overlapping Intervals
============================================================

  [PASS] Provided example
    Input : [[1,3], [2,6], [8,10], [15,18]]
    Output: [[1,6], [8,10], [15,18]]

  [PASS] Edge case: empty input
    Input : []  (empty)
    Output: []  (empty)
```

A failure adds the expected value:

```
  [FAIL] Edge case: equal values are not inversions
    Input   : [2, 2, 2, 2]
    Expected: 0
    Actual  : 6
```

## Note

`test_solutions.cpp` does `#include "../cpp/Assignment01_Suh.cpp"` and renames
its `main`, so the solution functions can be called directly without the
interactive menu. Run it from inside `test/` so the relative include resolves.
