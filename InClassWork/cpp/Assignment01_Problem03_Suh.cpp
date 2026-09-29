#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void selectionSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }

        int minVal = arr[minIdx];
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            swaps++;
        }

        cout << "Pass " << i + 1 << ": min = " << minVal
             << " at index " << minIdx << " -> ";
        printArray(arr, n);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, swaps;

    cout << "Original: ";
    printArray(A, n);
    selectionSort(A, n, comparisons, swaps);
    cout << "Sorted:   ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << "   Swaps: " << swaps << endl;

    return 0;
}
