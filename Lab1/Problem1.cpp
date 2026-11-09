// LAB 1 - PROBLEM 1
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// 1. Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// 3. Bubble Sort
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// 4. Quick Sort
int partitionAlg(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionAlg(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 5. Merge Sort
void merge(int a[], int l, int m, int r) {
    vector<int> left(a + l, a + m + 1);
    vector<int> right(a + m + 1, a + r + 1);
    int i = 0, j = 0, k = l;

    while (i < static_cast<int>(left.size()) && j < static_cast<int>(right.size())) {
        if (left[i] <= right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }
    while (i < static_cast<int>(left.size())) a[k++] = left[i++];
    while (j < static_cast<int>(right.size())) a[k++] = right[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// 6. Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 7. Copy the original array before each test
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = source[i];
    }
}

// 8. Measure all six algorithms on the same data.
void problem1(int originalArray[], int n) {
    cout << "LAB 1: PROBLEM 1 \n";
    
    int* arr = new int[n];
    clock_t start, end;
    double t;

    string fastest_alg = "";
    string slowest_alg = "";
    double min_time = 1e9;
    double max_time = -1.0;

    auto updateStats = [&](string name, double time_taken) {
        if (!is_sorted(arr, arr + n)) cout << "Error: incorrect sorting result\n";
        if (time_taken < min_time) {
            min_time = time_taken;
            fastest_alg = name;
        } else if (time_taken == min_time) fastest_alg += ", " + name;
        if (time_taken > max_time) {
            max_time = time_taken;
            slowest_alg = name;
        } else if (time_taken == max_time) slowest_alg += ", " + name;
    };

    copyArray(originalArray, arr, n);
    start = clock();
    insertionSort(arr, n);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Insertion Sort: " << t << " s\n";
    updateStats("Insertion Sort", t);

    copyArray(originalArray, arr, n);
    start = clock();
    selectionSort(arr, n);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Selection Sort: " << t << " s\n";
    updateStats("Selection Sort", t);

    copyArray(originalArray, arr, n);
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Bubble Sort: " << t << " s\n";
    updateStats("Bubble Sort", t);

    copyArray(originalArray, arr, n);
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Quick Sort: " << t << " s\n";
    updateStats("Quick Sort", t);

    copyArray(originalArray, arr, n);
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Merge Sort: " << t << " s\n";
    updateStats("Merge Sort", t);

    copyArray(originalArray, arr, n);
    start = clock();
    heapSort(arr, n);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << "Heap Sort: " << t << " s\n";
    updateStats("Heap Sort", t);

    cout << "\n=> Fastest: " << fastest_alg << " (" << min_time << " s)\n";
    cout << "=> Slowest: " << slowest_alg << " (" << max_time << " s)\n\n";

    delete[] arr;
}



// 9. Create a large random array and run the experiment.
int main() {
    const int SIZE = 10000;
    int* originalArray = new int[SIZE];
    
    srand(42); // Same seed in both files for repeatable comparisons.
    for (int i = 0; i < SIZE; ++i) {
        originalArray[i] = rand() % 100000;
    }

    problem1(originalArray, SIZE);
    

    delete[] originalArray;
    return 0;
}