#include <iostream>
#include <algorithm>
#include <ctime>     
#include <cstdlib>

using namespace std;


const int N = 1000000;


float goc[N];   
float a[N];     
float temp[N];  


void QuickSort(float a[], int left, int right) {
    
    float pivot = a[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) QuickSort(a, left, j);
    if (i < right) QuickSort(a, i, right);
}


void Heapify(float a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        Heapify(a, n, largest);
    }
}

void HeapSort(float a[], int n) {
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(a, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        Heapify(a, i, 0);
    }
}


void Merge(float a[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];

    
    for (int p = left; p <= right; p++) {
        a[p] = temp[p];
    }
}

void MergeSort(float a[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        MergeSort(a, left, mid);
        MergeSort(a, mid + 1, right);
        Merge(a, left, mid, right);
    }
}


void CopyArray() {
    for (int i = 0; i < N; i++) {
        a[i] = goc[i];
    }
}


int main() {
    cout << "Day\tQuicksort\tHeapsort\tMergesort\tsort (C++)" << endl;

    
    for (int test = 1; test <= 10; test++) {

      
        for (int i = 0; i < N; i++) {
            goc[i] = (float)rand() / RAND_MAX * 100000.0f;
        }

      
        if (test == 1) {
            sort(goc, goc + N);                    
        }
        else if (test == 2) {
            sort(goc, goc + N, greater<float>());   
        }
      
        CopyArray();
        clock_t start1 = clock();
        QuickSort(a, 0, N - 1);
        clock_t end1 = clock();
        double timeQuick = double(end1 - start1) * 1000.0 / CLOCKS_PER_SEC;

        CopyArray();
        clock_t start2 = clock();
        HeapSort(a, N);
        clock_t end2 = clock();
        double timeHeap = double(end2 - start2) * 1000.0 / CLOCKS_PER_SEC;

  
        CopyArray();
        clock_t start3 = clock();
        MergeSort(a, 0, N - 1);
        clock_t end3 = clock();
        double timeMerge = double(end3 - start3) * 1000.0 / CLOCKS_PER_SEC;


        CopyArray();
        clock_t start4 = clock();
        sort(a, a + N);
        clock_t end4 = clock();
        double timeStd = double(end4 - start4) * 1000.0 / CLOCKS_PER_SEC;

 
        cout << test << "\t"
            << (int)timeQuick << " ms\t\t"
            << (int)timeHeap << " ms\t\t"
            << (int)timeMerge << " ms\t\t"
            << (int)timeStd << " ms" << endl;
    }

    return 0;
}