#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n, int &comparisons, int &shifts) {
    comparisons = 0;
    shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;      // signed: j reaches -1 when key is a new minimum

        while (j >= 0) {
            comparisons++;
            if (arr[j] <= key) break;
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        arr[j + 1] = key;

        cout << "i = " << i << ", key = " << key << ": ";
        printArray(arr, n);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, shifts;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    insertionSort(A, n, comparisons, shifts);
    cout << "Sorted:   ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << "   Shifts: " << shifts << endl;

    // A is sorted now
    int B[8], C[8];
    for (int k = 0; k < n; k++) {
        B[k] = A[k];
        C[k] = A[n - 1 - k];
    }

    cout << endl << "=== Run 2: ascending order (fewest shifts) ===" << endl;
    cout << "Original: ";
    printArray(B, n);
    insertionSort(B, n, comparisons, shifts);
    cout << "Sorted:   ";
    printArray(B, n);
    cout << "Comparisons: " << comparisons << "   Shifts: " << shifts << endl;

    cout << endl << "=== Run 3: descending order (most shifts) ===" << endl;
    cout << "Original: ";
    printArray(C, n);
    insertionSort(C, n, comparisons, shifts);
    cout << "Sorted:   ";
    printArray(C, n);
    cout << "Comparisons: " << comparisons << "   Shifts: " << shifts << endl;

    return 0;
}
