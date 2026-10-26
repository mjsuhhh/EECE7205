# EECE 7205 — Assignment #01 (In-Class Work): Solutions

MyungJin Suh

Problems 1–6 sort A = {34, 7, 23, 32, 5, 62, 14, 19}, n = 8, into 5 7 14 19 23 32 34 62. Every program uses `printArray(const int arr[], int n)` for all array output, uses no library sorting function, and passes its counters by reference so `main()` prints the totals. All numbers below come from `output/`, produced by `./run_all.sh` on macOS with Apple clang 21. The counts are identical under Linux g++; only the running times depend on the machine.

| Problem | Algorithm | Result on A |
|---|---|---|
| 1 | Bubble Sort | 5 passes, 25 comparisons, 15 swaps (sorted copy: 1 pass, 7 comparisons) |
| 2 | Insertion Sort | 20 comparisons, 15 shifts |
| 3 | Selection Sort | 28 comparisons, 5 swaps |
| 4 | Quick Sort | 14 comparisons (sorted copy: 28) |
| 5 | Merge Sort | 17 comparisons, 7 of them in the final merge (sorted and reversed copies: 12) |
| 6 | Heap Sort | 12 swaps inside `siftDown` |

---

## Problem 1 — Bubble Sort

**Idea.** A pass walks left to right and swaps every neighbouring pair that is out of order. The largest value of the unsorted part wins each comparison it takes part in, so it is carried to the end of that part and never moves again; the unsorted part shrinks by one position per pass. A pass that makes no swap proves that every neighbouring pair is in order, so the sort stops.

```
Algorithm 1  Bubble Sort with early exit
Input:  array arr[0..n-1]
Output: arr in increasing order; passes, comparisons, swaps
 1: passes ← 0; comparisons ← 0; swaps ← 0
 2: for last ← n − 1 downto 1 do                ▷ unsorted part is arr[0..last]
 3:     swapped ← false
 4:     for j ← 0 to last − 1 do
 5:         comparisons ← comparisons + 1
 6:         if arr[j] > arr[j + 1] then
 7:             SWAP(arr[j], arr[j + 1])
 8:             swaps ← swaps + 1; swapped ← true
 9:         end if
10:     end for
11:     passes ← passes + 1
12:     PRINT-ARRAY(arr, n)
13:     if swapped = false then break
14: end for
```

| Pass | Comparisons | Swaps | Array after the pass (final values in bold) |
|---|---|---|---|
| 1 | 7 | 6 | 7 23 32 5 34 14 19 **62** |
| 2 | 6 | 3 | 7 23 5 32 14 19 **34 62** |
| 3 | 5 | 3 | 7 5 23 14 19 **32 34 62** |
| 4 | 4 | 3 | 5 7 14 19 **23 32 34 62** |
| 5 | 3 | 0 | 5 7 14 19 23 32 34 62 — no swap, stop |

**Correctness.** At the start of the pass with boundary `last`, arr[last+1..n−1] holds the largest values in their final order. Inside the pass, after positions j and j+1 are compared, arr[j+1] is the largest value in arr[0..j+1]; at the end of the pass the maximum of arr[0..last] is at arr[last], which extends the sorted suffix. If a pass makes no swap, arr[j] ≤ arr[j+1] holds for every j < last, and with the suffix property the whole array is sorted. The array only changes by swaps, so no value is lost or duplicated. The strict `>` never swaps equal neighbours, so Bubble Sort is stable.

**Complexity.** Each swap removes exactly one inversion (a pair i < j with arr[i] > arr[j]), so swaps = inversions = 15 for A. Worst case (reversed input): n − 1 full passes, n(n−1)/2 = 28 comparisons and swaps, Θ(n²). Best case (sorted input): one pass of n − 1 comparisons, Θ(n). Average case Θ(n²). Extra space Θ(1).

**Item 5.** On the sorted copy the program makes 1 pass, 7 comparisons and 0 swaps. In the first pass every neighbouring pair already satisfies arr[j] ≤ arr[j+1], so nothing is swapped, `swapped` stays false, and the loop ends. Without the flag the same input would still take 7 passes and 28 comparisons while nothing moves; the flag is what makes the best case Θ(n) instead of Θ(n²).

---

## Problem 2 — Insertion Sort

**Idea.** Keep a sorted prefix. Each step removes `key = arr[i]`, shifts the larger elements of the prefix one place right, and drops `key` into the gap.

```
Algorithm 2  Insertion Sort
Input:  array arr[0..n-1]
Output: arr in increasing order; comparisons, shifts
 1: comparisons ← 0; shifts ← 0
 2: for i ← 1 to n − 1 do
 3:     key ← arr[i]
 4:     j ← i − 1
 5:     while j ≥ 0 do
 6:         comparisons ← comparisons + 1
 7:         if arr[j] ≤ key then break
 8:         arr[j + 1] ← arr[j]
 9:         shifts ← shifts + 1
10:         j ← j − 1
11:     end while
12:     arr[j + 1] ← key
13:     PRINT-ARRAY(arr, n)
14: end for
```

| i | key | Comparisons | Shifts | Array after inserting key |
|---|---|---|---|---|
| 1 | 7 | 1 | 1 | 7 34 23 32 5 62 14 19 |
| 2 | 23 | 2 | 1 | 7 23 34 32 5 62 14 19 |
| 3 | 32 | 2 | 1 | 7 23 32 34 5 62 14 19 |
| 4 | 5 | 4 | 4 | 5 7 23 32 34 62 14 19 |
| 5 | 62 | 1 | 0 | 5 7 23 32 34 62 14 19 |
| 6 | 14 | 5 | 4 | 5 7 14 23 32 34 62 19 |
| 7 | 19 | 5 | 4 | 5 7 14 19 23 32 34 62 |
| | | **20** | **15** | |

The inner loop ends in one of two ways: `arr[j] ≤ key` costs one comparison that moves nothing (i = 5 is the extreme case), and `j = −1` ends it with no comparison at all (i = 1 and i = 4, where key is a new minimum). That is why comparisons (20) exceed shifts (15) by less than n − 1 = 7.

**Correctness.** Invariant: before step i, arr[0..i−1] holds the original first i elements in sorted order. Shifting the values greater than `key` one place right and writing `key` into the gap keeps arr[0..i] sorted. After the last step i = n − 1 the whole array is sorted. Equal values are never shifted past each other (`≤` stops the loop), so Insertion Sort is stable.

**Complexity.** Every shift removes exactly one inversion, so shifts S = number of inversions. With the handout's cost model T(n, S) = 6n − 2 + 3S: best case S = 0 gives 6n − 2 = 46, worst case S = n(n−1)/2 gives (3n² + 9n − 4)/2 = 130, and A (S = 15) gives 91. Best case Θ(n), average and worst case Θ(n²); in general Θ(n + S). Extra space Θ(1).

**Item 4.** The ascending order 5 7 14 19 23 32 34 62 causes the fewest shifts: 0 shifts and 7 comparisons, because each key is compared once with its left neighbour and stays. The descending order 62 34 32 23 19 14 7 5 causes the most: 28 shifts and 28 comparisons, because every pair is inverted and each key travels all the way to the front. Since each shift fixes one inversion, the shift count is exactly the inversion count: 0 for ascending, n(n−1)/2 = 28 for descending.

---

## Problem 3 — Selection Sort

**Idea.** Pass i scans the unsorted part arr[i..n−1] for its smallest value and swaps it into position i. The swap is skipped when the minimum is already there.

```
Algorithm 3  Selection Sort
Input:  array arr[0..n-1]
Output: arr in increasing order; comparisons, swaps
 1: comparisons ← 0; swaps ← 0
 2: for i ← 0 to n − 2 do
 3:     minIdx ← i
 4:     for j ← i + 1 to n − 1 do
 5:         comparisons ← comparisons + 1
 6:         if arr[j] < arr[minIdx] then minIdx ← j
 7:     end for
 8:     minVal ← arr[minIdx]
 9:     if minIdx ≠ i then
10:         SWAP(arr[i], arr[minIdx]); swaps ← swaps + 1
11:     end if
12:     print minVal, minIdx; PRINT-ARRAY(arr, n)
13: end for
```

| Pass | Minimum (index) | Swap? | Array after the pass |
|---|---|---|---|
| 1 | 5 (4) | 34 ↔ 5 | 5 7 23 32 34 62 14 19 |
| 2 | 7 (1) | no | 5 7 23 32 34 62 14 19 |
| 3 | 14 (6) | 23 ↔ 14 | 5 7 14 32 34 62 23 19 |
| 4 | 19 (7) | 32 ↔ 19 | 5 7 14 19 34 62 23 32 |
| 5 | 23 (6) | 34 ↔ 23 | 5 7 14 19 23 62 34 32 |
| 6 | 32 (7) | 62 ↔ 32 | 5 7 14 19 23 32 34 62 |
| 7 | 34 (6) | no | 5 7 14 19 23 32 34 62 |

Comparisons: 7 + 6 + 5 + 4 + 3 + 2 + 1 = 28. Swaps: 5.

**Correctness.** Invariant: before pass i, arr[0..i−1] holds the i smallest values in their final positions. Pass i finds the minimum of arr[i..n−1], the (i+1)-th smallest value overall, and places it at arr[i]. After pass n − 2 the last element is the largest by elimination.

**Complexity.** The comparisons do not depend on the order of the data: always n(n−1)/2, so best, average and worst case are all Θ(n²). Swaps are at most n − 1. The handout's cost model gives T(n) = (3n² + 9n − 4)/2 + r + s, where r counts `minIdx` updates and s counts swaps; for A, r = 8 and s = 5, so T = 130 + 13 = 143. Extra space Θ(1). The long-distance swap can jump a value over an equal one, so Selection Sort is not stable.

**Item 4.** Selection Sort makes 5 swaps on A; Bubble Sort makes 15. Bubble Sort only exchanges neighbours, and each such swap removes exactly one inversion, so it needs as many swaps as A has inversions. Selection Sort first finds the minimum using comparisons alone and then moves it straight to its final position, so it makes at most one swap per pass, and none when the minimum is already in place (passes 2 and 7). One long swap can remove many inversions at once: the first swap, 34 ↔ 5, removes 7 of A's 15. The price is paid in comparisons: Selection Sort always makes 28, while Bubble Sort makes 25 on A and only 7 on sorted input.

---

## Problem 4 — Quick Sort (Lomuto partition, last element as pivot)

**Idea.** Partition arr[low..high] around pivot = arr[high] so that smaller values end up to its left and the rest to its right, which puts the pivot in its final position. Then sort the two sides recursively.

```
Algorithm 4  Quick Sort
Input:  array arr, indices low and high
Output: arr[low..high] in increasing order; comparisons
 1: procedure QUICK-SORT(arr, low, high, depth)
 2:     if low ≥ high then return
 3:     print 3·depth spaces, "pivot = ", arr[high]; PRINT-ARRAY(arr + low, high − low + 1)
 4:     p ← PARTITION(arr, low, high)
 5:     QUICK-SORT(arr, low, p − 1, depth + 1)
 6:     QUICK-SORT(arr, p + 1, high, depth + 1)
 7: end procedure
 8: procedure PARTITION(arr, low, high)
 9:     pivot ← arr[high]; i ← low − 1
10:     for j ← low to high − 1 do             ▷ arr[low..i] < pivot ≤ arr[i+1..j−1]
11:         comparisons ← comparisons + 1
12:         if arr[j] < pivot then
13:             i ← i + 1; SWAP(arr[i], arr[j])
14:         end if
15:     end for
16:     SWAP(arr[i + 1], arr[high])
17:     return i + 1
18: end procedure
```

First partition (pivot 19), the lines marked `|` in the output:

| j | arr[j] | arr[j] < 19? | i | Array after the step |
|---|---|---|---|---|
| 0 | 34 | no | −1 | 34 7 23 32 5 62 14 19 |
| 1 | 7 | yes: swap arr[0], arr[1] | 0 | 7 34 23 32 5 62 14 19 |
| 2, 3 | 23, 32 | no | 0 | unchanged |
| 4 | 5 | yes: swap arr[1], arr[4] | 1 | 7 5 23 32 34 62 14 19 |
| 5 | 62 | no | 1 | unchanged |
| 6 | 14 | yes: swap arr[2], arr[6] | 2 | 7 5 14 32 34 62 23 19 |
| end | | swap arr[3], arr[7] | | 7 5 14 **19** 34 62 23 32 |

The pivot 19 lands at index 3. Recursion tree printed by the program:

```
pivot = 19: 34 7 23 32 5 62 14 19
   pivot = 14: 7 5 14
      pivot = 5: 7 5
   pivot = 32: 34 62 23 32
      pivot = 62: 34 62
```

Comparisons: 7 + 2 + 1 + 3 + 1 = 14.

**Correctness.** The partition loop keeps arr[low..i] < pivot and arr[i+1..j−1] ≥ pivot. When the loop ends, swapping the pivot into position i + 1 leaves smaller values on its left and the others on its right, so the pivot is in its final place. By induction on the subarray size, the recursive calls sort both sides, and since no value crosses the pivot the whole range is sorted.

**Complexity.** A call on k elements makes k − 1 comparisons. Balanced splits give T(n) = 2T(n/2) + Θ(n) = Θ(n log n), which is also the average case for random input (about 1.39 n log₂ n comparisons). Splits of sizes n − 1 and 0 at every level give (n−1) + (n−2) + … + 1 = n(n−1)/2 comparisons, Θ(n²). Extra space is the recursion stack: Θ(log n) for balanced splits, Θ(n) in the worst case. Not stable.

**Item 5.** On the sorted copy Quick Sort makes 28 comparisons, the maximum n(n−1)/2, and the recursion tree becomes a chain seven levels deep. With the last element as pivot, a sorted subarray always hands the partition its own maximum: every other value is smaller, `i` advances together with `j` (the trace shows i = j at every step, so every swap is a self-swap), and the pivot stays at the end. Each call removes only one element from the problem. A reversed array is just as bad, with the minimum as pivot every time. The fix is to stop choosing a predictable pivot: swap a randomly chosen element into arr[high] before partitioning, which gives an expected Θ(n log n) comparisons on every input, or use the median of arr[low], arr[mid] and arr[high] (median-of-three), which picks the true middle of a sorted or reversed subarray.

---

## Problem 5 — Merge Sort

**Idea.** Split the range at mid = ⌊(low + high)/2⌋, sort both halves recursively, and merge the two sorted halves by repeatedly taking the smaller front value.

```
Algorithm 5  Merge Sort
Input:  array arr, indices low and high
Output: arr[low..high] in increasing order; comparisons
 1: procedure MERGE-SORT(arr, low, high)
 2:     if low ≥ high then return
 3:     print "split: "; PRINT-ARRAY(arr + low, high − low + 1)
 4:     mid ← ⌊(low + high) / 2⌋
 5:     MERGE-SORT(arr, low, mid)
 6:     MERGE-SORT(arr, mid + 1, high)
 7:     MERGE(arr, low, mid, high)
 8:     print "merged: "; PRINT-ARRAY(arr + low, high − low + 1)
 9: end procedure
10: procedure MERGE(arr, low, mid, high)
11:     L ← copy of arr[low..mid]; R ← copy of arr[mid + 1..high]
12:     i ← 0; j ← 0; k ← low
13:     while i < |L| and j < |R| do
14:         comparisons ← comparisons + 1
15:         if L[i] ≤ R[j] then arr[k] ← L[i]; i ← i + 1
16:         else arr[k] ← R[j]; j ← j + 1
17:         k ← k + 1
18:     end while
19:     copy what is left of L, then of R, into arr[k..high]   ▷ no comparisons
20: end procedure
```

| Merge | Left | Right | Result | Comparisons |
|---|---|---|---|---|
| 1 | 34 | 7 | 7 34 | 1 |
| 2 | 23 | 32 | 23 32 | 1 |
| 3 | 7 34 | 23 32 | 7 23 32 34 | 3 |
| 4 | 5 | 62 | 5 62 | 1 |
| 5 | 14 | 19 | 14 19 | 1 |
| 6 | 5 62 | 14 19 | 5 14 19 62 | 3 |
| 7 (final) | 7 23 32 34 | 5 14 19 62 | 5 7 14 19 23 32 34 62 | 7 |
| | | | | **17** |

| Input | Comparisons | Final merge |
|---|---|---|
| A | 17 | 7 |
| Sorted copy | 12 | 4 |
| Reversed copy | 12 | 4 |

**Correctness.** During a merge, arr[low..k−1] holds the smallest k − low values of L and R in sorted order, and L[i] and R[j] are the smallest values not yet placed, so taking the smaller of the two preserves this. When one half runs out, the rest of the other half is already sorted and larger. By induction on the subarray size, MERGE-SORT sorts every range. Taking from L on ties (`≤`) keeps equal values in their original order, so Merge Sort is stable.

**Complexity.** T(n) = 2T(n/2) + Θ(n) = Θ(n log n) in the best, average and worst case: the split tree has log₂ 8 = 3 levels and each level merges all n values. A merge of halves of sizes a and b makes between min(a, b) and a + b − 1 comparisons, so for n = 8 every input costs between (n/2) log₂ n = 12 and n log₂ n − n + 1 = 17 comparisons. A reaches the maximum because every merge interleaves its halves completely; sorted and reversed input reach the minimum because one half runs out after min(a, b) comparisons in every merge.

**Item 5.** The split tree depends only on n, so the same seven merges happen for every input of size 8, and the data only decides how early each merge runs out of one half. That confines the comparison count to the narrow band 12–17. Bubble Sort ranges from 7 (sorted) to 28 (reversed) and Quick Sort from 14 (A) to 28 (sorted or reversed), because their amount of work (the number of passes, the balance of each partition) depends on the order itself. Merge Sort needs Θ(n) extra memory for the temporary copies L and R (the final merge copies all n values), plus a Θ(log n) recursion stack, so it does not sort in place.

---

## Problem 6 — Heap Sort

**Idea.** View the array as a binary tree where the children of index k are at 2k + 1 and 2k + 2. First rearrange it into a max-heap (every parent ≥ its children), so the maximum is at the root. Then repeatedly swap the root to the end of the heap, shrink the heap by one, and sift the new root down to restore the heap.

```
Algorithm 6  Heap Sort
Input:  array arr[0..n-1]
Output: arr in increasing order; swaps made inside SIFT-DOWN
 1: procedure SIFT-DOWN(arr, root, size)
 2:     loop
 3:         largest ← root; left ← 2·root + 1; right ← 2·root + 2
 4:         if left < size and arr[left] > arr[largest] then largest ← left
 5:         if right < size and arr[right] > arr[largest] then largest ← right
 6:         if largest = root then return
 7:         SWAP(arr[root], arr[largest]); swaps ← swaps + 1
 8:         root ← largest
 9:     end loop
10: end procedure
11: procedure HEAP-SORT(arr, n)
12:     for root ← ⌊n/2⌋ − 1 downto 0 do SIFT-DOWN(arr, root, n)   ▷ build the max-heap
13:     print "Heap: "; PRINT-ARRAY(arr, n)
14:     for end ← n − 1 downto 1 do
15:         SWAP(arr[0], arr[end])                   ▷ the maximum reaches its final place
16:         SIFT-DOWN(arr, 0, end)
17:         PRINT-ARRAY(arr, end); PRINT-ARRAY(arr + end, n − end)
18:     end for
19: end procedure
```

Building the heap from A:

| root | Value | Sift-down | Swaps |
|---|---|---|---|
| 3 | 32 | child 19 is smaller, stays | 0 |
| 2 | 23 | swaps with child 62 | 1 |
| 1 | 7 | swaps with 32, then with 19 | 2 |
| 0 | 34 | swaps with 62; 34 ≥ 23 and 14, stops | 1 |

Heap after the build phase: 62 32 34 19 5 23 14 7

```
                 62
              /      \
            32        34
           /  \      /  \
         19    5   23    14
        /
       7
```

Sorting phase (the program prints the two parts on two aligned lines, because `printArray` ends its line):

| end | Heap part | Sorted part | Swaps in this sift-down |
|---|---|---|---|
| 7 | 34 32 23 19 5 7 14 | 62 | 2 |
| 6 | 32 19 23 14 5 7 | 34 62 | 2 |
| 5 | 23 19 7 14 5 | 32 34 62 | 1 |
| 4 | 19 14 7 5 | 23 32 34 62 | 2 |
| 3 | 14 5 7 | 19 23 32 34 62 | 1 |
| 2 | 7 5 | 14 19 23 32 34 62 | 0 |
| 1 | 5 | 7 14 19 23 32 34 62 | 0 |

Swaps inside `siftDown`: 4 while building + 8 while sorting = 12. The root-to-end swaps in HEAP-SORT itself are not counted, as the handout asks.

**Correctness.** SIFT-DOWN turns a subtree whose two child subtrees are heaps into a heap, so processing the parents from ⌊n/2⌋ − 1 down to 0 builds a max-heap bottom-up (the leaves are heaps already). In the sorting phase the invariant is: arr[0..end] is a max-heap holding the end + 1 smallest values, and arr[end+1..n−1] holds the largest values in sorted order. Swapping the root, the largest heap value, into arr[end] extends the sorted part by one, and sifting down restores the heap on arr[0..end−1].

**Complexity.** Building the heap costs Θ(n), because most nodes sit near the bottom and can only sift down a short distance. Each of the n − 1 extractions sifts down at most ⌊log₂ n⌋ levels, so the sort is Θ(n log n) in the worst case, and typically in every case. Extra space Θ(1): the heap lives inside the array and `siftDown` is iterative.

**Item 5.** Heap Sort is not stable. Take three packets keyed by timestamp, with the letter recording arrival order: [4A, 4C, 1D]. The array is already a max-heap (4A ≥ both children; the tie with 4C causes no swap). For end = 2 the root 4A is swapped to the end, giving [1D, 4C, 4A], and sifting down moves 4C to the root: [4C, 1D, 4A]. For end = 1, 4C is swapped behind 1D: [1D, 4C, 4A]. The result lists 4C before 4A, the reverse of their arrival order. The swap of the root with arr[end] moves a value across the whole heap without looking at the equal values it jumps over, and the heap order says nothing about how equal keys should be arranged. Even two equal values [4A, 4C] come out as [4C, 4A].

---

## Problem 7 — Comparing the Six Algorithms

The program contains the six sorting functions from Problems 1–6 with their printing removed, each counting comparisons into a `long long`, and runs four experiments. Random data comes from `mt19937` with the fixed seed 7205, taking `1 + rng() % 100000`; the standard fully specifies `mt19937`, so every compiler produces the same arrays. Every measurement sorts a fresh copy of the same data, and the copy is made outside the timed region.

```
Algorithm 7  Timing experiment
Input:  the six sorting procedures; sizes n ∈ {1000, 5000, 10000}
Output: average time and comparison count for every algorithm and size
 1: rng ← MT19937(7205)
 2: run every algorithm once, untimed, on 5000 values from a separate generator   ▷ warm-up
 3: for each size n do
 4:     data ← n values 1 + rng() mod 100000
 5:     for each algorithm SORT do
 6:         total ← 0
 7:         repeat 5 times
 8:             work ← copy of data                       ▷ outside the timed region
 9:             start ← NOW(); SORT(work, n, comparisons); stop ← NOW()
10:             total ← total + (stop − start)
11:         end repeat
12:         time[SORT][n] ← total / 5
13:         check that work is sorted; keep its first 10 values
14:     end for
15: end for
16: print the tables; PRINT-ARRAY(first 10 values, 10) for each of the 18 sorted arrays
```

### Part 1 — comparisons on the eight-element inputs

| Algorithm | A | Sorted copy | Reversed copy |
|---|---|---|---|
| Bubble Sort | 25 | 7 | 28 |
| Insertion Sort | 20 | 7 | 28 |
| Selection Sort | 28 | 28 | 28 |
| Quick Sort | 14 | 28 | 28 |
| Merge Sort | 17 | 12 | 12 |
| Heap Sort | 26 | 27 | 24 |

Heap Sort makes fewer comparisons on the reversed copy because a decreasing array is already a max-heap, so the build phase moves nothing.

### Part 2 — random arrays (macOS, Apple clang 21, `-O2`, average of 5 runs)

Running time in milliseconds:

| Algorithm | n = 1,000 | n = 5,000 | n = 10,000 | 10,000 / 1,000 | 10,000 / 5,000 |
|---|---|---|---|---|---|
| Bubble Sort | 0.249 | 5.534 | 21.375 | 85.8 | 3.86 |
| Insertion Sort | 0.072 | 1.425 | 5.484 | 76.3 | 3.85 |
| Selection Sort | 0.848 | 18.644 | 72.648 | 85.7 | 3.90 |
| Quick Sort | 0.015 | 0.109 | 0.261 | 17.8 | 2.38 |
| Merge Sort | 0.062 | 0.248 | 0.477 | 7.7 | 1.93 |
| Heap Sort | 0.022 | 0.134 | 0.305 | 13.7 | 2.28 |

Comparisons on the same arrays:

| Algorithm | n = 1,000 | n = 5,000 | n = 10,000 | 10,000 / 1,000 | 10,000 / 5,000 |
|---|---|---|---|---|---|
| Bubble Sort | 498,720 | 12,489,115 | 49,980,465 | 100.2 | 4.00 |
| Insertion Sort | 252,765 | 6,345,041 | 24,844,387 | 98.3 | 3.92 |
| Selection Sort | 499,500 | 12,497,500 | 49,995,000 | 100.1 | 4.00 |
| Quick Sort | 10,570 | 71,293 | 148,018 | 14.0 | 2.08 |
| Merge Sort | 8,721 | 55,262 | 120,523 | 13.8 | 2.18 |
| Heap Sort | 16,866 | 107,611 | 235,530 | 14.0 | 2.19 |

Theory: from 1,000 to 10,000 values, n² grows 100× and n log n about 13.3×; from 5,000 to 10,000, n² grows 4× and n log n about 2.16×.

### Part 3 — correctness check

`printArray` prints the first 10 elements of all 18 sorted arrays (six algorithms × three sizes). For each size the six lines are identical, for example `24 29 39 51 52 64 65 76 85 85` for n = 10,000, and a full element-by-element check confirms that all 18 arrays are in order. The repeated 85 shows that duplicate values are handled.

### Part 4 — almost sorted input (n = 5,000, sorted, then 50 random neighbouring pairs swapped)

| Algorithm | Time (ms) | Comparisons |
|---|---|---|
| Bubble Sort | 0.004 | 14,994 |
| Insertion Sort | 0.003 | 5,049 |
| Selection Sort | 18.344 | 12,497,500 |
| Quick Sort | 3.121 | 12,367,288 |
| Merge Sort | 0.158 | 32,025 |
| Heap Sort | 0.125 | 112,100 |

### Item 4 — discussion

**Which grow like n² and which like n log n?** Bubble, Insertion and Selection Sort grow like n²: each is a pair of nested loops whose inner loop runs Θ(n) times on random data. Merge and Heap Sort grow like n log n in every case, and Quick Sort does on random data, where its partitions are reasonably balanced.

**Do the measurements agree with the theory?** The comparison counts agree almost exactly: going from 1,000 to 10,000 values they grow by 98–100× for the three quadratic sorts and by 13.8–14.0× for the other three (theory: 100 and 13.3), and from 5,000 to 10,000 by 3.92–4.00× versus 2.08–2.19× (theory: 4 and 2.16). The running times show the same split, most cleanly from 5,000 to 10,000: 3.85–3.90× for the quadratic sorts and 1.93–2.38× for the n log n sorts. The ratios measured from n = 1,000 are noisier (76–86× and 8–18×) because the fast sorts finish in 15–62 microseconds there, where cache warm-up, CPU frequency changes and timer overhead are as large as the work being measured. Merge Sort's time grows the least, probably because a large part of its cost is allocating the 2(n − 1) temporary vectors, a cost that grows like n rather than n log n. Constant factors also show up inside each group: Insertion Sort is about 4× faster than Bubble Sort because it makes half as many comparisons and shifts values instead of swapping them. At n = 10,000 the gap between the groups is large: Selection Sort takes 72.6 ms and Quick Sort 0.26 ms, about 280× less.

**Large random array.** Quick Sort was the fastest here and sorts in place with only a recursion stack, so it is the choice for large random arrays, but with a random or median-of-three pivot rather than the last element, so that a sorted or nearly sorted input cannot trigger its Θ(n²) case (Part 4 shows what that case costs). When a guaranteed Θ(n log n) bound is required, Heap Sort gives it without extra memory, and Merge Sort gives it together with stability at the cost of Θ(n) extra memory.

**Almost sorted array.** Insertion Sort. Its running time is Θ(n + I), where I is the number of inversions, so on almost sorted data it does little more than one pass: 5,049 comparisons, which is n − 1 plus one for each of the 50 swapped pairs. Bubble Sort with the early-exit flag also did well (3 passes, 14,994 comparisons), but only because every value was at most two positions from its place; a single small value near the end moves left only one position per pass and would force about n passes, while Insertion Sort would handle it in a single insertion step. Selection Sort gains nothing from sorted input (always n(n−1)/2 comparisons), Heap Sort does not benefit either, and Quick Sort with the last-element pivot comes close to its worst case: 12.4 million comparisons, about 1,000 times slower than Insertion Sort on the same data.
