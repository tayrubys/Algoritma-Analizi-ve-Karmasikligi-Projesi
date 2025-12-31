#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

//İleri Yönlü Lineer Arama
int forwardLinearSearch(int A[], int N, int key) {
    /*base case*/
    if(N==0) return -1;
    if (A[0] == key) return 0;
    int result = forwardLinearSearch(A + 1, N - 1, key);
    if (result == -1) return -1;
    return 1 + result;
}

//Geri Yönlü Lineer Arama
int BackwardLinearSearch(int A[],int N,int key){
    /*base case*/
    if(N==0) return -1;
    if(key==A[N-1]) return N-1;
    /*divide &conquer &merge*/
    return BackwardLinearSearch(A,N-1,key);
}

//İkili Arama
int BinarySearch(int A[],int key,int left,int right){
    /*base case*/
    if(left>right) return -1;

    int middle=(left+right)/2;
    if(key==A[middle]) return middle;

    else if(key<A[left]){
        return BinarySearch(A,key,left,middle-1);
    }
    else{
        return BinarySearch(A,key,middle+1,right);
    }
}

int main() {
    srand(time(0));
    int N = 10000;
    int tekrarSayisi = 10000; 
    
    vector<int> data(N);
    for (int i = 0; i < N; i++) {
        data[i] = i * 2; 
    }

    int* arr = data.data(); 

    int randomIndex = rand() % N; 
    int aranan = data[randomIndex]; 

    cout << "ARAMA ALGORITMALARIN PERFORMANS TESTI" << endl;
    cout << "Dizi Boyutu  : " << N << endl;
    cout << "Tekrar Sayisi: " << tekrarSayisi << endl;
    cout << "Aranan Eleman: " << aranan << " (Index: " << randomIndex << ")" << endl;
    cout << "----------------------------------" << endl;

    //TEST 1: Ileri Yonlu Arama
    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < tekrarSayisi; i++) {
        forwardLinearSearch(arr, N, aranan);
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
    cout << "Ileri Yonlu Arama Suresi : " << duration1.count() << " ms" << endl;
    cout << "----------------------------------" << endl;

    //TEST 2: Geri Yonlu Arama
    auto start2 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < tekrarSayisi; i++) {
        BackwardLinearSearch(arr, N, aranan);
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
    cout << "Geri Yonlu Arama Suresi  : " << duration2.count() << " ms" << endl;
    cout << "----------------------------------" << endl;

    //TEST 3: Ikili Arama (Binary Search)
    auto start3 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < tekrarSayisi; i++) {
        BinarySearch(arr, aranan, 0, N - 1);
    }
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop3 - start3);
    cout << "Binary Search Suresi     : " << duration3.count() << " ms" << endl;
    cout << "----------------------------------" << endl;
    
    return 0;
}