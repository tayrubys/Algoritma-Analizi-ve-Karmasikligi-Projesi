#define NOMINMAX
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
//A[0..N-1] dizisi için problem aşağıdaki 4 yaklaşımla çözülecektir:

//Algorithm 1 for Max Subsequence Sum o(n^3)
int maxSubSum1(const vector<int>& a){
 int maxSum=0;
 for(int i=0;i<(int)a.size();i++){
    for(int j=i;j<(int)a.size();j++){
      int thisSum=0;
      for(int k=i;k<=j;k++){
        thisSum+=a[k];
      }
      if(thisSum>maxSum){
         maxSum=thisSum;
      }
    }
 }
 return maxSum;
}

//Algorithm 2 for Max Subsequence Sum o(n^2)
int maxSubSum2(const vector<int>& a){
 int maxSum=0;
 for(int i=0;i<(int)a.size();i++){
    int thisSum=0;
    for(int j=i;j<(int)a.size();j++){
        thisSum+=a[j];
        if(thisSum>maxSum){
            maxSum=thisSum;
        }
    }
 }
 return maxSum;
}

//Algorithm 3 for Max Subsequence Sum o(nlogn)
// Yardımcı fonksiyon: 3 tamsayı arasından en büyüğünü bulur
int max3(int a, int b, int c) {
    return max(a, max(b, c));
}
int maxSubSumRec(const vector<int>& a, int left, int right) {
    //tek eleman kaldıysa
    if (left == right) {
        return (a[left] > 0) ? a[left] : 0;
    }
    int center = (left + right) / 2; 
    //sol yarıdaki max bul
    int maxLeftSum = maxSubSumRec(a, left, center);

    //sağ yarıdaki max bul 
    int maxRightSum = maxSubSumRec(a, center + 1, right);
    //sola doğru en büyük toplamı bul
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; i--) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    //sağa doğru en büyük toplamı bul
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int i = center + 1; i <= right; i++) {
        rightBorderSum += a[i];
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
    //sol sağ ve orta arasından en büyüğünü döndür
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}
// Algoritma 3 Ana Fonksiyonu (Driver)
int maxSubSum3(const vector<int>& a) {
    return maxSubSumRec(a, 0, a.size() - 1);
}
//Algorithm 4 for Max Subsequence Sum o(n)
int maxSubSum4(const vector<int>& a){
 int maxSum=0,thisSum=0;
 for(int j=0;j<(int)a.size();j++){
    thisSum+=a[j];
    if(thisSum>maxSum){
        maxSum=thisSum;
    }
    else if(thisSum<0){
            thisSum=0;
    }
 }
 return maxSum;
}

int main(){

    cout<<"MAXIMUM SUBSEQUENCE PROBLEMI"<<endl;
    int N=1500;
    vector<int> testDizisi(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (int i = 0; i < N; i++) {
        testDizisi[i] = dis(gen);
    }

   //maxSubSum1 testi
    auto baslangic = std::chrono::high_resolution_clock::now();
    int sonuc1 = maxSubSum1(testDizisi);
    auto bitis = std::chrono::high_resolution_clock::now();
    auto sure = std::chrono::duration_cast<std::chrono::milliseconds>(bitis - baslangic);
    cout << "Algoritma 1.O(n^3): " << sure.count() << " ms \t| Sonuc: " << sonuc1 << endl;
    cout<<"----------------------------------------"<<endl;

    //maxSubSum2 testi
    baslangic = std::chrono::high_resolution_clock::now();
    int sonuc2 = maxSubSum2(testDizisi); 
    bitis = std::chrono::high_resolution_clock::now();
    sure = std::chrono::duration_cast<std::chrono::milliseconds>(bitis - baslangic);
    cout << "Algoritma 2.O(n^2): " << sure.count() << " ms \t| Sonuc: " << sonuc2 << endl;
    cout<<"----------------------------------------"<<endl;
    
    //maxSubSum3 testi
    baslangic = std::chrono::high_resolution_clock::now();
    int sonuc3 = maxSubSum3(testDizisi); 
    bitis = std::chrono::high_resolution_clock::now();
    sure = std::chrono::duration_cast<std::chrono::milliseconds>(bitis - baslangic);
    cout << "Algoritma 3.O(nlogn): " << sure.count() << " ms \t| Sonuc: " << sonuc3 << endl;
    cout<<"----------------------------------------"<<endl;
    
    //maxSubSum4 testi
    baslangic = std::chrono::high_resolution_clock::now();
    int sonuc4 = maxSubSum4(testDizisi);
    bitis = std::chrono::high_resolution_clock::now();
    sure = std::chrono::duration_cast<std::chrono::milliseconds>(bitis - baslangic);
    cout << "Algoritma 4.O(n):    " << sure.count() << " ms \t| Sonuc: " << sonuc4 << endl; 
    cout<<"----------------------------------------"<<endl;
}