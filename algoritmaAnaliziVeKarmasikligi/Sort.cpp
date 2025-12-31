#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

using namespace std;

void SWAP(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//SELECTIONSORT
void SelectionSort(int A[],int N){
   for(int i=0;i<N-1;i++){
    int minIndex=i;
    for(int j=i+1;j<N;j++){
        if(A[j]<A[minIndex]) minIndex=j;
    }
    if(i!=minIndex) SWAP(&A[i],&A[minIndex]);
   } 
}

//BUBBLSORT
void BubbleSort(int A[],int N){
    for(int i=0;i<N;i++){
        for(int j=1;j<(N-1);j++){
            if(A[j-1]>A[j]) SWAP(&A[j-1],&A[j]);
        }
    }
}

//INSERTIONSORT
void InsertionSort(int A[],int N){
    int j,P,Tmp;
    for(P=1;P<N;P++){
        Tmp=A[P];
        for(j=P;j>0 && A[j-1]>Tmp;j--){
            A[j]=A[j-1];
        }
        A[j]=Tmp;
    }
}

//MERGESORT
//merge
void Merge(int A[],int leftCount,int rightCount){
    int n = leftCount + rightCount;
    int* temp = new int[n]; 
    int i = 0;
    int j = leftCount;
    int k = 0;
    while (i < leftCount && j < n) {
        if (A[i] <= A[j]) temp[k++] = A[i++];
        else temp[k++] = A[j++];
    }
    while (i < leftCount) temp[k++] = A[i++];
    while (j < n) temp[k++] = A[j++];
    for (i = 0; i < n; i++) A[i] = temp[i];
    delete[] temp;
}
//ms
void MS(int A[], int N) {
    if (N <= 1) return;
    int middle = N / 2;
    
    MS(A, middle);            
    MS(&A[middle], N - middle); 
    
    Merge(A, middle, N - middle); //birlestirme
}

//QUICKSORT
int Partition(int A[], int N) {
   if (N <= 1) return 0;
    int pivot = A[0]; 
    int i = 1;
    int j = N - 1;

    while(1){
        while(A[j]>pivot) j--;
        while(A[i]<pivot && i < j) i++;
        if(i>=j) break;
        SWAP(&A[j],&A[0]);
        i++; 
        j--;
    }
    SWAP(&A[j],&A[0]);
    return j;
}
void QS(int A[],int N){
    if (N <= 1) return;
    int index = Partition(A, N);
    //sol tarafı sırala
    QS(A, index);
   //sağ tarafı sırala
   QS(&A[index + 1], N - index - 1);
}

//HEAPSORT
void Heapify(int A[], int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && A[left] > A[largest]) largest = left;
    if (right < N && A[right] > A[largest]) largest = right;

    if (largest != i) {
        SWAP(&A[i], &A[largest]);
        Heapify(A, N, largest);
    }
}
void HeapSort(int A[],int N){
    for (int i = N / 2 - 1; i >= 0; i--) Heapify(A, N, i);
    for (int i = N - 1; i > 0; i--) {
        SWAP(&A[0], &A[i]);
        Heapify(A, i, 0);
    }
}

//COUNTINGSORT
void CountingSort(int A[],int N){
    if (N == 0) return;
    int maxVal = A[0];
    for(int i=1; i<N; i++) if(A[i] > maxVal) maxVal = A[i];
    
    int* count = new int[maxVal + 1](); 
    int* output = new int[N];
    for (int i = 0; i < N; i++) count[A[i]]++;
    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];

    for (int i = N - 1; i >= 0; i--) {
        output[count[A[i]] - 1] = A[i];
        count[A[i]]--;
    }
    for (int i = 0; i < N; i++) A[i] = output[i];
    delete[] count;
    delete[] output;
}

//RADIXSORT
void RadixSort(int A[],int N){
    int maxVal = A[0];
    for (int i = 1; i < N; i++) if(A[i] > maxVal) maxVal = A[i];

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int* output = new int[N];
        int count[10] = {0};
        
        for (int i = 0; i < N; i++) count[(A[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        
        for (int i = N - 1; i >= 0; i--) {
            output[count[(A[i] / exp) % 10] - 1] = A[i];
            count[(A[i] / exp) % 10]--;
        }
        
        for (int i = 0; i < N; i++) A[i] = output[i];
        delete[] output;
    }
}

//EXTERNALSORT
void ExternalSortSim(int A[], int N) {
    int K = 4; 
    int parcaBoyutu = N / K;

    if (parcaBoyutu == 0) return;

    for (int i = 0; i < K; i++) {
        int baslangic = i * parcaBoyutu;
        int boyut = (i == K - 1) ? (N - baslangic) : parcaBoyutu;
        
        QS(&A[baslangic], boyut);
    }
    
    int* sonucDizisi = new int[N];  
    int* indeksler = new int[K]();  

    for (int i = 0; i < N; i++) {
        int enKucukDeger = INT_MAX;
        int secilenParca = -1;

        for (int p = 0; p < K; p++) {
            int pBaslangic = p * parcaBoyutu;
            int pBoyut = (p == K - 1) ? (N - pBaslangic) : parcaBoyutu;

            if (indeksler[p] < pBoyut) {
                int deger = A[pBaslangic + indeksler[p]];
                if (deger < enKucukDeger) {
                    enKucukDeger = deger;
                    secilenParca = p;
                }
            }
        }

        if (secilenParca != -1) {
            sonucDizisi[i] = enKucukDeger;
            indeksler[secilenParca]++; 
        }
    }

    for (int i = 0; i < N; i++) A[i] = sonucDizisi[i];

    delete[] sonucDizisi;
    delete[] indeksler;
}

int main(){
    cout << "  SIRALAMA ALGORITMALARI " << endl << endl;

    srand(time(0));
    
    int N = 15000; 
    
    int* originalData = new int[N];
    for(int i=0; i<N; i++) {
        originalData[i] = rand() % 50000;
    }
    int* testData = new int[N];
    cout << "Eleman Sayisi: " << N << endl << endl;

    // Selection Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    auto start = chrono::high_resolution_clock::now();
    SelectionSort(testData, N);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Selection Sort: " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Insertion Sort 
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    InsertionSort(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Insertion Sort: " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Bubble Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    BubbleSort(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Bubble Sort:    " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Merge Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    MS(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Merge Sort:     " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Quick Sort 
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    QS(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Quick Sort:     " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Heap Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    HeapSort(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Heap Sort:      " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // 7. Counting Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    CountingSort(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Counting Sort:  " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // Radix Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    RadixSort(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Radix Sort:     " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    // External Sort
    for(int i=0; i<N; i++) testData[i] = originalData[i];
    start = chrono::high_resolution_clock::now();
    ExternalSortSim(testData, N);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "External Sort:  " << duration.count() << " ms" << endl;
    cout << "---------------"<< endl;

    delete[] originalData;
    delete[] testData;

    return 0;
}