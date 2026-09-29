#include <iostream>
#include <vector>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void merge(int arr[], int low, int mid, int high, int &comparisons) {
    vector<int> left(arr + low, arr + mid + 1);
    vector<int> right(arr + mid + 1, arr + high + 1);
    int nLeft = left.size(), nRight = right.size();
    int i = 0, j = 0, k = low;

    while (i < nLeft && j < nRight) {
        comparisons++;
        if (left[i] <= right[j]) arr[k++] = left[i++];   // <= (not <) keeps the sort stable
        else                     arr[k++] = right[j++];
    }
    while (i < nLeft)  arr[k++] = left[i++];
    while (j < nRight) arr[k++] = right[j++];
}

// The top-level merge runs last, so finalMerge ends up holding its count
void mergeSort(int arr[], int low, int high, int &comparisons, int &finalMerge) {
    if (low >= high) return;

    cout << "split:  ";
    printArray(arr + low, high - low + 1);

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid, comparisons, finalMerge);
    mergeSort(arr, mid + 1, high, comparisons, finalMerge);

    int before = comparisons;
    merge(arr, low, mid, high, comparisons);
    finalMerge = comparisons - before;

    cout << "merged: ";
    printArray(arr + low, high - low + 1);
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, finalMerge;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(A, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted:   ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << "   (final merge: " << finalMerge << ")" << endl;

    // A is sorted now
    int sortedCopy[8], reversedCopy[8];
    for (int k = 0; k < n; k++) {
        sortedCopy[k] = A[k];
        reversedCopy[k] = A[n - 1 - k];
    }

    cout << endl << "=== Run 2: sorted copy of A ===" << endl;
    cout << "Original: ";
    printArray(sortedCopy, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(sortedCopy, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted:   ";
    printArray(sortedCopy, n);
    cout << "Comparisons: " << comparisons << "   (final merge: " << finalMerge << ")" << endl;

    cout << endl << "=== Run 3: reversed copy of A ===" << endl;
    cout << "Original: ";
    printArray(reversedCopy, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(reversedCopy, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted:   ";
    printArray(reversedCopy, n);
    cout << "Comparisons: " << comparisons << "   (final merge: " << finalMerge << ")" << endl;

    return 0;
}
