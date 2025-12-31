#include <iostream>
#include <chrono>   
#include <iomanip>  
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

//iş zamanı problemi
struct Job
{
   int id;     
   int time;
};
//aktivite problemi
struct Activity
{
    int id;     
    int start;  
    int finish;
};

// Huffman ağacı dugumu
struct MinHeapNode {
    char data;             
    unsigned freq;             
    struct MinHeapNode *left, *right; 
};
// Min Heap 
struct MinHeap {
    unsigned size;     // mevcut eleman sayısı
    unsigned capacity; 
    struct MinHeapNode** array; // düğüm pointer dizisi
};
// Yeni düğüm oluşturma
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Min Heap oluşturma
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// İki düğümü swap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

   if (left < (int)minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq){
        smallest = left;
    }

   if (right < (int)minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq){
        smallest = right;
    }

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

//en kucuk frekanslı dugumu al
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

//insert
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// Heap'i diziden inşa etme
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

//job problemi yardımcı fonk
void SwapJobs(Job* a, Job* b) {
    Job temp = *a;
    *a = *b; 
    *b = temp;
}
int PartitionJobs(Job A[], int low, int high) {
    int pivot = A[high].time; // Süreye göre sırala
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (A[j].time < pivot) { // Küçükten büyüğe
            i++;
            SwapJobs(&A[i], &A[j]);
        }
    }
    SwapJobs(&A[i + 1], &A[high]);
    return (i + 1);
}
void QuickSortJobs(Job A[], int low, int high) {
    if (low < high) {
        int pi = PartitionJobs(A, low, high);
        QuickSortJobs(A, low, pi - 1);
        QuickSortJobs(A, pi + 1, high);
    }
}

//İŞ ZAMANLAMA
void GreedyJobScheduler(Job jobs[], int N) {
    //sıralama
    QuickSortJobs(jobs, 0, N - 1);

    cout << "Siralama (En Kisa Is Once): ";
    for(int i=0; i<N; i++) cout << "J" << jobs[i].id << "(" << jobs[i].time << ") ";
    cout << endl;

    int currentTime = 0;
    long long totalCompletionTime = 0;

    cout << "Tamamlanma Sureleri: ";
    for (int i = 0; i < N; i++) {
        currentTime += jobs[i].time; // İşin bitiş zamanı
        totalCompletionTime += currentTime;
        cout << currentTime << " ";
    }
    cout << endl;

    double averageTime = (double)totalCompletionTime / N;
    cout << "Ortalama Tamamlanma Suresi: " << averageTime << endl;
}

//activite problemiyardımcı fonk
void SwapActivities(Activity* a, Activity* b) {
    Activity temp = *a; *a = *b; *b = temp;
}
int PartitionActivities(Activity A[], int low, int high) {
    int pivot = A[high].finish; // Bitiş süresine göre sırala
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (A[j].finish < pivot) { 
            i++;
            SwapActivities(&A[i], &A[j]);
        }
    }
    SwapActivities(&A[i + 1], &A[high]);
    return (i + 1);
}
void QuickSortActivities(Activity A[], int low, int high) {
    if (low < high) {
        int pi = PartitionActivities(A, low, high);
        QuickSortActivities(A, low, pi - 1);
        QuickSortActivities(A, pi + 1, high);
    }
}

//AKTİVİTE SECİMİ
void ActivityScheduling(Activity activities[], int N) {
    // bitiş zamanına gore sıralama
    QuickSortActivities(activities, 0, N - 1);

    cout << "Bitis Suresine Gore Sirali Liste: " << endl;
    for(int i=0; i<N; i++) {
        cout << "a" << activities[i].id << ": [" << activities[i].start << "-" << activities[i].finish << "] ";
    }
    cout << endl << endl;

    cout << "Secilen Aktiviteler (Greedy): ";
    
    int prev = 0; 
    cout << "a" << activities[prev].id << " ";

    for (int i = 1; i < N; i++) {
        if (activities[i].start >= activities[prev].finish) {
            cout << "a" << activities[i].id << " "; 
            prev = i; 
        }
    }
    cout << endl;
}

//HUFFMAN AĞACI OLUŞTURMA
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
     //min heap olusturma
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    while (minHeap->size != 1) {
        // en kucuk iki dugumu al
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Yeni iç düğüm oluştur (Frekansların toplamı) [cite: 300]
        // '$' işareti iç düğüm olduğunu gösterir.
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Kalan son düğüm kök
    return extractMin(minHeap);
}

//ENCODE
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    // Sola gidiyorsan 0
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    // Sağa gidiyorsan 1
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        cout << root->data << ": ";
        for (int i = 0; i < top; ++i)
            cout << arr[i];
        cout << endl;
    }
}

//DECODE
void decodeHuffman(struct MinHeapNode* root, string encodedStr) {
    struct MinHeapNode* curr = root;
    cout << "Decode Edilen Metin: ";
    
    for (int i = 0; i < (int)encodedStr.length(); i++) {
        if (encodedStr[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (isLeaf(curr)) {
            cout << curr->data;
            curr = root; // Tekrar köke dön
        }
    }
    cout << endl;
}

int main() {

    cout<<"GREEDY ALGORITMALAR"<<endl;

    // 1. İŞ ZAMANLAMA
    cout << "GREEDY 1: IS ZAMANLAMA PROBLEMI" << endl;
    Job jobs[] = { {1, 15}, {2, 8}, {3, 3}, {4, 10} };
    int nJobs = sizeof(jobs) / sizeof(jobs[0]);

    auto start = chrono::high_resolution_clock::now();
    GreedyJobScheduler(jobs, nJobs);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Calisma Suresi: " << duration.count() << " ms" << endl << endl;
    cout<<"--------------------"<<endl;

    // 2. AKTİVİTE SEÇİMİ 
    cout << " GREEDY 2: AKTIVITE ZAMANLAMA PROBLEMI" << endl;
    Activity activities[] = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7},
        {5, 3, 8}, {6, 5, 9}, {7, 6, 10}, {8, 8, 11},
        {9, 8, 12}, {10, 2, 13}, {11, 12, 14}
    };
    int nActivities = sizeof(activities) / sizeof(activities[0]);

    start = chrono::high_resolution_clock::now();
    ActivityScheduling(activities, nActivities);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Calisma Suresi: " << duration.count() << " ms" << endl << endl;
    cout<<"--------------------"<<endl;

    // 3. HUFFMAN KODLAMA TESTİ
    cout << "GREEDY 3: HUFFMAN KODLAMA" << endl;

    char data[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    int freq[] = { 5, 48, 7, 17, 10, 13 };
    int size = sizeof(data) / sizeof(data[0]);

    start = chrono::high_resolution_clock::now();
    
    // Ağacı oluştur
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    
    //Encode/decode işlemi
    int arr[100], top = 0;
    cout << "--- Karakter Kodlari (Encode) ---" << endl;
    printCodes(root, arr, top);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Agac Olusturma Suresi: " << duration.count() << " ms" << endl << endl;

    cout << "--- Decode Testi ---" << endl;
    string sampleEncodedStr = "1011100"; // Örnek rastgele bitler
    cout << "Girdi (Bits): " << sampleEncodedStr << endl;
    decodeHuffman(root, sampleEncodedStr);

    return 0;
}
