#include <iostream>
#include <chrono>   
#include <cstdlib>  
#include <climits>  

using namespace std;

void SWAP(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//heapify
void Heapify(int A[], int N, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && A[left] < A[smallest])
        smallest = left;

    if (right < N && A[right] < A[smallest])
        smallest = right;

    if (smallest != i) {
        SWAP(&A[i], &A[smallest]);
        Heapify(A, N, smallest); 
    }
}

//insert
void InsertKey(int A[], int* N, int key) {
    
    (*N)++; 
    int i = *N - 1;
    A[i] = key;

    while (i != 0 && A[(i - 1) / 2] > A[i]) {
        SWAP(&A[i], &A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//findmin
int FindMin(int A[], int N) {
    // Eğer yığın boşsa hata değeri döndür
    if (N <= 0) return INT_MAX;
    
    // Kök düğümü döndür
    return A[0];
}
//deletemin
int DeleteMin(int A[], int* N) {
    if (*N <= 0) return INT_MAX; 
    if (*N == 1) {
        (*N)--;
        return A[0];
    }

    int root = A[0];

    A[0] = A[*N - 1];
    (*N)--;

    Heapify(A, *N, 0);

    return root;
}

//build
void BuildHeap(int A[], int N) {
    int startIdx = (N / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        Heapify(A, N, i);
    }
}

//increase key
void IncreaseKey(int A[], int N, int i, int delta) {
    if (i < 0 || i >= N) return;
    A[i] += delta;
    Heapify(A, N, i); 
}

//decrease key
void DecreaseKey(int A[], int i, int delta) {
    if (i < 0) return;
    A[i] -= delta;
    
    while (i != 0 && A[(i - 1) / 2] > A[i]) {
        SWAP(&A[i], &A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//delete key
void DeleteKey(int A[], int* N, int i) {
    if (i < 0 || i >= *N) return;

    A[i] = A[*N - 1];
    (*N)--;
    Heapify(A, *N, i);
}

//merge
int* MergeHeaps(int H1[], int N1, int H2[], int N2, int* newSize) {
    *newSize = N1 + N2;
    int* result = (int*)malloc(sizeof(int) * (*newSize)); 

    for (int i = 0; i < N1; i++) {
        result[i] = H1[i];
    }

    for (int i = 0; i < N2; i++) {
        result[N1 + i] = H2[i];
    }

    BuildHeap(result, *newSize);

    return result;
}

int main() {

    cout << " HEAP YAPILARI" << endl << endl;
    srand(time(0));
    const int CAPACITY = 20000;
    int* minHeap = (int*)malloc(sizeof(int) * CAPACITY);
    int heapSize = 0;

    // insert
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 5000; i++) {
        InsertKey(minHeap, &heapSize, rand() % 10000);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Insert: 5000 eleman eklendi. (FindMin: " << minHeap[0] << ")" << endl;
    cout << "Sure: " << duration.count() << " ms" << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // find min
    start = chrono::high_resolution_clock::now();
    int currentMin = FindMin(minHeap, heapSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "FindMin: Su anki En Kucuk Deger: " << currentMin << endl;
    cout << "Sure: " << duration.count() << " ms" << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // delete min
    start = chrono::high_resolution_clock::now();
    int minVal = DeleteMin(minHeap, &heapSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "DeleteMin: Silinen En Kucuk: " << minVal << ". Yeni Min: " << minHeap[0] << endl;
    cout << "Sure: " << duration.count() << " ms" << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // decrease key
    int oldVal = minHeap[10];
    DecreaseKey(minHeap, 10, 5000);
    cout << "DecreaseKey: Indeks 10 (" << oldVal << ") -> 5000 azaltildi -> " << minHeap[10] << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // increase key 
    // Kök elemanı arttır
    oldVal = minHeap[0];
    IncreaseKey(minHeap, heapSize, 0, 5000); // Kökü 5000 arttır
    cout << "IncreaseKey: Kok (" << oldVal << ") -> 5000 arttirildi. Yeni Min: " << minHeap[0] << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // delete key
    // Rastgele bir indeksi sil
    int deleteIndex = 5;
    cout << "DeleteKey: Indeks " << deleteIndex << " siliniyor" << endl;
    DeleteKey(minHeap, &heapSize, deleteIndex);
    cout << "Islem Tamamlandi." << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // build heao
    int rawArray[10] = {20, 6, 3, 10, 16, 2, 10, 14, 8, 7}; 
    int rawN = 10;
    cout << "BuildHeap: Ornek Dizi: 20, 6, 3, 10" << endl;
    
    start = chrono::high_resolution_clock::now();
    BuildHeap(rawArray, rawN);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    
    cout << "Heap Hali (Ilk 5): ";
    for(int i=0; i<5; i++) cout << rawArray[i] << " ";
    cout << endl << "Sure: " << duration.count() << " ms" << endl << endl;
    cout<<"------------------------------------------------"<<endl;

    // merge
    cout << "Merge: Iki Heap Birlestiriliyor (H1 + H2)" << endl;
    int h2Size = 1000;
    int* heap2 = (int*)malloc(sizeof(int) * h2Size);
    for(int i=0; i<h2Size; i++) heap2[i] = rand() % 10000;
    BuildHeap(heap2, h2Size); // H2'yi heap yap

    int mergedSize = 0;
    start = chrono::high_resolution_clock::now();
    int* mergedHeap = MergeHeaps(minHeap, heapSize, heap2, h2Size, &mergedSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    
    cout << "Birlestirilen Boyut: " << mergedSize << endl;
    cout << "Sure: " << duration.count() << " ms" << endl;

    // Temizle
    free(minHeap);
    free(heap2);
    free(mergedHeap);

    return 0;
}