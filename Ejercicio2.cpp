#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& A, int p, int r) {
    for (int i = p + 1; i <= r; ++i) {
        int key = A[i];
        int j = i - 1;

        while (j >= p && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }

        A[j + 1] = key;
    }
}

void merge(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; ++i) left[i] = A[p + i];
    for (int j = 0; j < n2; ++j) right[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            A[k] = left[i];
            ++i;
        } else {
            A[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        A[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        A[k] = right[j];
        ++j;
        ++k;
    }
}

void hybridMergeSort(vector<int>& A, int p, int r, int k) {
    if (p >= r) return;

    if (r - p + 1 <= k) {
        insertionSort(A, p, r);
        return;
    }

    int q = p + (r - p) / 2;
    hybridMergeSort(A, p, q, k);
    hybridMergeSort(A, q + 1, r, k);
    merge(A, p, q, r);
}

int main() {
    const int n = 1000000;
    vector<int> baseArray(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000000);

    for (int i = 0; i < n; ++i) {
        baseArray[i] = dist(gen);
    }

    vector<int> ks = {1, 2, 4, 8, 16, 32, 64, 128};

    cout << "Evaluando tiempos para n = " << n << " elementos\n";
    cout << "--------------------------------------------------\n";

    for (int k : ks) {
        vector<int> testArray = baseArray;

        auto inicio = high_resolution_clock::now();
        hybridMergeSort(testArray, 0, n - 1, k);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "k = " << k << "\t| Tiempo: " << duracion.count() << " us\n";
    }

    cout << "\nNota: k = 1 se comporta como Merge Sort estandar.\n";
    return 0;
}