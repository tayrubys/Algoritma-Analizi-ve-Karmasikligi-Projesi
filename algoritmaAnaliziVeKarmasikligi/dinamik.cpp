#include <iostream>
#include <algorithm> 
#include <climits>   // INT_MAX 

using namespace std;

//Bottom-Up DP Fiboncacci
int BottomUpDP(int n) {
    if (n == 0) return 0;
    int* SolTable = new int[n + 1];//bellekta yer aciyoruz
    //base case
    SolTable[0] = 0;
    SolTable[1] = 1;

    for (int i = 2; i <= n; i++) {
        SolTable[i] = SolTable[i - 1] + SolTable[i - 2];
    }

    int result = SolTable[n];

    delete[] SolTable; 
    return result;
}

//Minimum Maliyet Yol Problemi (Top-Down)
#define N 3
// Matris Tanimi
int M[N][N] = {
    {1, 5, 0}, 
    {2, 4, 2},
    {1, 3, 0}
};
//Cozum Tablosu 
int MemoPath[N][N];
void InitMemoPath() {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            MemoPath[i][j] = -1;
}
// Recursive Fonksiyon
int MinimumCostPath(int i, int j) {

    if (i == N - 1 && j == N - 1) return M[i][j];//hedefe ulasıldı mı

    //Daha once hesaplandiysa tablodan don
    if (MemoPath[i][j] != -1) return MemoPath[i][j];

    //Asagi gitme maliyeti
    int downCost = INT_MAX;
    if (i + 1 <= N - 1) {
        downCost = MinimumCostPath(i + 1, j);
    }

    //Saga gitme maliyeti
    int rightCost = INT_MAX;
    if (j + 1 <= N - 1) {
        rightCost = MinimumCostPath(i, j + 1);
    }

    //Min olani sec
    int minCost = downCost;
    if (rightCost < minCost) minCost = rightCost;

    // Kendi maliyetini ekle, kaydet ve don
    MemoPath[i][j] = M[i][j] + minCost;
    return MemoPath[i][j];
}


//Sırt Çantası Problemi
int v[] = {30, 20, 100, 90, 160}; //degerler
int w[] = {5, 10, 20, 30, 40};    //agirliklar

// Tablo: [Esya Sayisi + 1][Kapasite + 1]
int MemoKnap[6][61]; 

void InitKnapMemo() {
    for(int i=0; i<6; i++){
        for(int j=0; j<61; j++){
            MemoKnap[i][j] = -1;
        }
    }        
}

int Knapsack(int n, int W) {
    //base case
    if (n <= 0 || W <= 0) return 0;
    // Tabloda varsa oradan al
    if (MemoKnap[n][W] != -1) return MemoKnap[n][W];

    int currentWeight = w[n-1];
    int currentValue = v[n-1];

    //durum1: esyayi almama
    int leave_val = Knapsack(n - 1, W);

    //durum2: esyayi alma - eger sigiyorsa
    int take_val = -1; 
    if (currentWeight <= W) {
        take_val = currentValue + Knapsack(n - 1, W - currentWeight);
    }

    MemoKnap[n][W] = max(leave_val, take_val);
    return MemoKnap[n][W];
}


int main() {
    cout << "  DINAMIK PROGRAMLAMA " << endl << endl;

    //Fibonacci
    int fib = 8;
    cout << "1. Fibonacci(" << fib << "): " << BottomUpDP(fib) << endl;
    cout << "----------------------------------" << endl;

    //Min Yol
    InitMemoPath(); // Tabloyu temizle
    cout << "2. Min Maliyet ((0,0) -> (2,2)): " << MinimumCostPath(0, 0) << endl;
    cout << "----------------------------------" << endl;

    //Sirt Cantasi
    InitKnapMemo();
    int esyaSayisi = 5;
    int capacity = 60;
    cout << "3. Sirt Cantasi Max Deger: " << Knapsack(esyaSayisi, capacity) << endl;
    cout << "----------------------------------" << endl;

    return 0;
}