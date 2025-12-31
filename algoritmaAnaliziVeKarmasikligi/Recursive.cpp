#include <iostream>
#include <vector>

using namespace std;

//1+2+...+n
int Sum(int n,int& sayac){
    sayac++;
    /*base case*/
    if(n==1) return 1;
    /*divide and conquer */
    int partialSum=Sum(n-1,sayac);
    /*merge*/
    return partialSum+n;
}

// Dizi toplamı
int sumArray(int A[],int N,int& sayac){
    sayac++;
  /*base case*/
  if(N==1) return A[0];
  /*divide conquer*/
  int localSum=sumArray(A,N-1,sayac);
  /*merge*/
  return localSum+A[N-1];
}

//a^n 
double Power(double a,int n,int& sayac){
    sayac++;
    double pr;
    /*base case */
    if(n==0) return 1;
    if(n==1) return a;
    /*partial result=a^(n/2')*/
    pr=Power(a,n/2,sayac);
    /*merge*/
    double result=pr*pr;
    /*is "n" odd*/
    if(n%2) result*=a;
    return result;
}

//Fibonacci Sayıları
int Fibonacci(int n,int& sayac){
    sayac++;
    /*base case */
    if(n==0) return 0;
    if(n==1) return 1;

    return Fibonacci(n-1,sayac)+Fibonacci(n-2,sayac);
}

//Tower of Hanoi
void ToH(int n,int src,int target,int aux,int& sayac){
    sayac++;
   if(n<=0) return;
   /*move the first n-1 items from src to aux*/
   ToH(n-1,src,aux,target,sayac);
   cout << n << ". diski " << src << "'den " << target << "'ye tasi" << endl;
   ToH(n-1,aux,target,src,sayac);
}

//Recursive Digit Sum
int superDigit(int n,int& sayac){
    sayac++;
    if(n<10) return n;
    int digitSum=0;
    while(n>0){
        digitSum+=n%10;
        n=n/10;
    }
    return superDigit(digitSum,sayac);
}

int main(){
    cout<<"REKURSIF ALGORITMALAR CAGRI SAYISI"<<endl;
    //sum
    int count=0;
    cout<<"Sum(10):"<<Sum(10,count);
    cout << "Cagri sayisi: " << count << endl;
    cout << "---------------"<< endl;

    //dizi toplamı
    count=0;
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    int boyut = sizeof(arr)/sizeof(arr[0]);
    cout<<"sumArray(arr):"<<sumArray(arr,boyut,count);
    cout << "Cagri sayisi: " << count << endl;
    cout << "---------------"<< endl;

    //power
    count=0;
    cout << "Power(2^10): " << Power(2, 10, count);
    cout << "Cagri sayisi: " << count << endl;
    cout << "---------------"<< endl;

    //fibonacci 
    count=0;
    cout << "Fibonacci(10): " << Fibonacci(10, count);
    cout << "Cagri sayisi: " << count << endl;

    //hanoi
    count=0;
    ToH(3, 1, 3, 2, count);
    cout << "Hanoi(3, 1, 3, 2) Cagri sayisi:"<< count <<endl;
    cout << "---------------"<< endl;

    //sıper digit
    count=0;
    cout << "SuperDigit(9875): " << superDigit(9875, count);
    cout << "Cagri sayisi: " << count << endl;
    cout << "---------------"<< endl;

}