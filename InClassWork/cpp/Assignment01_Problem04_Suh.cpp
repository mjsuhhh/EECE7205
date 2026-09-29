#include <iostream>
#include <string>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

int partition(int arr[], int low, int high, int &comparisons, bool showSteps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            if (showSteps) {
                cout << "  | swap  i = " << i << ", j = " << j << ": ";
                printArray(arr + low, high - low + 1);
            }
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    if (showSteps) {
        cout << "  | pivot " << pivot << " placed at index " << i + 1 << ": ";
        printArray(arr + low, high - low + 1);
    }
    return i + 1;
}

void quickSort(int arr[], int low, int high, int &comparisons, int depth = 0) {
    if (low >= high) return;

    cout << string(3 * depth, ' ') << "pivot = " << arr[high] << ": ";
    printArray(arr + low, high - low + 1);

    int p = partition(arr, low, high, comparisons, depth == 0);
    quickSort(arr, low, p - 1, comparisons, depth + 1);
    quickSort(arr, p + 1, high, comparisons, depth + 1);
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    comparisons = 0;
    quickSort(A, 0, n - 1, comparisons);
    cout << "Sorted:   ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << endl;

    int sortedCopy[8];                  // A is sorted now
    for (int k = 0; k < n; k++) sortedCopy[k] = A[k];

    cout << endl << "=== Run 2: already sorted copy of A ===" << endl;
    cout << "Original: ";
    printArray(sortedCopy, n);
    comparisons = 0;
    quickSort(sortedCopy, 0, n - 1, comparisons);
    cout << "Sorted:   ";
    printArray(sortedCopy, n);
    cout << "Comparisons: " << comparisons << endl;

    return 0;
}
