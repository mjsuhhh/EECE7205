// Compile with -O2 for timing: g++ -std=c++17 -O2 -o compare Assignment01_Problem07_Suh.cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <utility>
#include <string>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

// Problem 1: Bubble Sort
void bubbleSort(int arr[], int n, long long &comparisons) {
    for (int last = n - 1; last > 0; last--) {
        bool swapped = false;
        for (int j = 0; j < last; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Problem 2: Insertion Sort
void insertionSort(int arr[], int n, long long &comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] <= key) break;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Problem 3: Selection Sort
void selectionSort(int arr[], int n, long long &comparisons) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

// Problem 4: Quick Sort
int partition(int arr[], int low, int high, long long &comparisons) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, long long &comparisons) {
    if (low >= high) return;
    int p = partition(arr, low, high, comparisons);
    quickSort(arr, low, p - 1, comparisons);
    quickSort(arr, p + 1, high, comparisons);
}

// Problem 5: Merge Sort
void merge(int arr[], int low, int mid, int high, long long &comparisons) {
    vector<int> left(arr + low, arr + mid + 1);
    vector<int> right(arr + mid + 1, arr + high + 1);
    int nLeft = left.size(), nRight = right.size();
    int i = 0, j = 0, k = low;
    while (i < nLeft && j < nRight) {
        comparisons++;
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else                     arr[k++] = right[j++];
    }
    while (i < nLeft)  arr[k++] = left[i++];
    while (j < nRight) arr[k++] = right[j++];
}

void mergeSort(int arr[], int low, int high, long long &comparisons) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid, comparisons);
    mergeSort(arr, mid + 1, high, comparisons);
    merge(arr, low, mid, high, comparisons);
}

// Problem 6: Heap Sort
void siftDown(int arr[], int root, int size, long long &comparisons) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        if (left < size) {
            comparisons++;
            if (arr[left] > arr[largest]) largest = left;
        }
        if (right < size) {
            comparisons++;
            if (arr[right] > arr[largest]) largest = right;
        }
        if (largest == root) return;
        swap(arr[root], arr[largest]);
        root = largest;
    }
}

void heapSort(int arr[], int n, long long &comparisons) {
    for (int root = n / 2 - 1; root >= 0; root--)
        siftDown(arr, root, n, comparisons);
    for (int end = n - 1; end >= 1; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, 0, end, comparisons);
    }
}

// Wrappers so all six sorts share one signature
void quickSortAll(int arr[], int n, long long &comparisons) { quickSort(arr, 0, n - 1, comparisons); }
void mergeSortAll(int arr[], int n, long long &comparisons) { mergeSort(arr, 0, n - 1, comparisons); }

typedef void (*SortFunction)(int arr[], int n, long long &comparisons);
struct Algorithm {
    const char *name;
    SortFunction sort;
};
const Algorithm ALGORITHMS[] = {
    {"Bubble Sort", bubbleSort},      {"Insertion Sort", insertionSort},
    {"Selection Sort", selectionSort}, {"Quick Sort", quickSortAll},
    {"Merge Sort", mergeSortAll},      {"Heap Sort", heapSort}};
const int NUM_ALGORITHMS = 6;

bool isSorted(const int arr[], int n) {
    for (int k = 1; k < n; k++)
        if (arr[k - 1] > arr[k]) return false;
    return true;
}

// Sorts a fresh copy of data; returns the time in ms
double timedSort(const Algorithm &algorithm, const vector<int> &data,
                 vector<int> &work, long long &comparisons) {
    work = data;
    comparisons = 0;
    auto start = chrono::steady_clock::now();
    algorithm.sort(work.data(), (int)work.size(), comparisons);
    auto stop = chrono::steady_clock::now();
    return chrono::duration<double, milli>(stop - start).count();
}

int main() {
    // Part 1: comparisons on A, sorted A and reversed A
    const int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    const int n = sizeof(A) / sizeof(A[0]);
    vector<int> original(A, A + n), sortedA(A, A + n), reversedA(n), work;
    long long unused = 0;
    insertionSort(sortedA.data(), n, unused);      // no library sort allowed
    for (int k = 0; k < n; k++) reversedA[k] = sortedA[n - 1 - k];

    cout << "=== Part 1: comparisons on the eight-element inputs ===" << endl;
    cout << left << setw(16) << "Algorithm" << right << setw(8) << "A"
         << setw(8) << "Sorted" << setw(10) << "Reversed" << endl;
    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        long long cA, cS, cR;
        timedSort(ALGORITHMS[a], original, work, cA);
        timedSort(ALGORITHMS[a], sortedA, work, cS);
        timedSort(ALGORITHMS[a], reversedA, work, cR);
        cout << left << setw(16) << ALGORITHMS[a].name << right << setw(8) << cA
             << setw(8) << cS << setw(10) << cR << endl;
    }

    // Part 2: timing and comparisons on random arrays
    const int SIZES[] = {1000, 5000, 10000};
    const int NUM_SIZES = 3;
    const int REPEATS = 5;
    // mt19937 is fully specified, so every compiler generates the same data
    mt19937 rng(7205);

    double avgMs[NUM_ALGORITHMS][NUM_SIZES];
    long long comps[NUM_ALGORITHMS][NUM_SIZES];
    int firstTen[NUM_ALGORITHMS][NUM_SIZES][10];
    bool allSorted = true;

    // Untimed warm-up; its own generator leaves the measured data unchanged
    mt19937 warmRng(1);
    vector<int> warm(5000);
    for (int &x : warm) x = 1 + warmRng() % 100000;
    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        long long ignored;
        timedSort(ALGORITHMS[a], warm, work, ignored);
    }

    for (int s = 0; s < NUM_SIZES; s++) {
        vector<int> data(SIZES[s]);
        for (int &x : data) x = 1 + rng() % 100000;
        for (int a = 0; a < NUM_ALGORITHMS; a++) {
            double total = 0;
            for (int r = 0; r < REPEATS; r++)
                total += timedSort(ALGORITHMS[a], data, work, comps[a][s]);
            avgMs[a][s] = total / REPEATS;
            if (!isSorted(work.data(), SIZES[s])) allSorted = false;
            for (int k = 0; k < 10; k++) firstTen[a][s][k] = work[k];
        }
    }

    cout << endl << "=== Part 2a: average running time in ms on random arrays ("
         << REPEATS << " runs each) ===" << endl;
    cout << left << setw(16) << "Algorithm" << right;
    for (int s = 0; s < NUM_SIZES; s++) cout << setw(12) << ("n = " + to_string(SIZES[s]));
    cout << setw(12) << "10000/1000" << setw(12) << "10000/5000" << endl;
    cout << fixed << setprecision(3);
    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        cout << left << setw(16) << ALGORITHMS[a].name << right;
        for (int s = 0; s < NUM_SIZES; s++) cout << setw(12) << avgMs[a][s];
        cout << setw(12) << setprecision(1) << avgMs[a][2] / avgMs[a][0]
             << setw(12) << setprecision(2) << avgMs[a][2] / avgMs[a][1]
             << setprecision(3) << endl;
    }

    cout << endl << "=== Part 2b: comparisons on the same random arrays ===" << endl;
    cout << left << setw(16) << "Algorithm" << right;
    for (int s = 0; s < NUM_SIZES; s++) cout << setw(12) << ("n = " + to_string(SIZES[s]));
    cout << setw(12) << "10000/1000" << setw(12) << "10000/5000" << endl;
    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        cout << left << setw(16) << ALGORITHMS[a].name << right;
        for (int s = 0; s < NUM_SIZES; s++) cout << setw(12) << comps[a][s];
        cout << setw(12) << setprecision(1) << (double)comps[a][2] / comps[a][0]
             << setw(12) << setprecision(2) << (double)comps[a][2] / comps[a][1]
             << setprecision(3) << endl;
    }
    cout << "Theory, 1000 -> 10000: n^2 grows 100x, n log n about 13.3x" << endl
         << "Theory, 5000 -> 10000: n^2 grows 4x,   n log n about 2.16x" << endl;

    // Part 3: first 10 elements of every sorted array
    cout << endl << "=== Part 3: first 10 elements of each sorted array ===" << endl;
    for (int s = 0; s < NUM_SIZES; s++) {
        cout << "n = " << SIZES[s] << endl;
        for (int a = 0; a < NUM_ALGORITHMS; a++) {
            cout << "  " << left << setw(16) << ALGORITHMS[a].name << right;
            printArray(firstTen[a][s], 10);
        }
    }
    cout << "Full check of all " << NUM_ALGORITHMS * NUM_SIZES << " sorted arrays: "
         << (allSorted ? "every element is in order" : "ERROR, an array is out of order")
         << endl;

    // Part 4: almost sorted input
    const int NEAR_N = 5000, NEAR_SWAPS = 50;
    vector<int> nearly(NEAR_N);
    for (int k = 0; k < NEAR_N; k++) nearly[k] = 20 * (k + 1);
    for (int t = 0; t < NEAR_SWAPS; t++) {
        int p = rng() % (NEAR_N - 1);
        swap(nearly[p], nearly[p + 1]);
    }

    cout << endl << "=== Part 4: almost sorted input (n = " << NEAR_N << ", "
         << NEAR_SWAPS << " random neighbour swaps, " << REPEATS << " runs each) ===" << endl;
    cout << left << setw(16) << "Algorithm" << right << setw(12) << "time (ms)"
         << setw(14) << "comparisons" << endl;
    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        long long c = 0;
        double total = 0;
        for (int r = 0; r < REPEATS; r++) total += timedSort(ALGORITHMS[a], nearly, work, c);
        cout << left << setw(16) << ALGORITHMS[a].name << right << setw(12) << total / REPEATS
             << setw(14) << c << endl;
    }

    return 0;
}
