#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// Kod, Microsoft Visual Studio kullanýlarak C++ diliyle geliþtirilmiþtir. Sorunsuz derleme ve çalýþtýrma için ayný geliþtirme ortamýnýn kullanýlmasý önerilir.
/**
 * Bucket Sort Algoritmasý
 * @param arr: Sýralanacak float vektörü
 * @param n:   Oluþturulacak kova sayýsý
 */
void bucketSort(vector<float>& arr, int n)
{
    // Hata Kontrolü: Boþ dizi veya kova sayýsý geçersizliði
    if (arr.empty() || n <= 0)
        return;

    // 1. ADIM: Dizideki minimum ve maksimum deðerleri bulma
    // Bu deðerler normalizasyon formülünde kullanýlýr
    float minVal = arr[0];
    float maxVal = arr[0];

    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // range: Tüm dizi aralýðýný temsil eder, formülde payda olarak kullanýlýr
    float range = maxVal - minVal;

    // range=0 ise tüm elemanlar eþittir, bölme hatasý oluþmadan erken çýk
    if (range == 0)
        return;

    // 2. ADIM: n tane boþ kova oluþturma
    vector<vector<float>> buckets(n);

    // 3. ADIM: Elemanlarý uygun kovalara yerleþtirme 
    for (size_t i = 0; i < arr.size(); i++)
    {
        // Normalizasyon Formülü:
        // bucketIndex = (x - minVal) * (n-1) / range
        // Bu formül her elemaný [0, n-1] aralýðýna eþler.
        // minVal her zaman kova[0]'a, maxVal kova[n-1]'e gider.
        int bucketIndex = (int)((arr[i] - minVal) * (n - 1) / range);

        // Güvenlik kontrolü
        if (bucketIndex >= n) bucketIndex = n - 1;  // Üst sýnýr
        if (bucketIndex < 0)  bucketIndex = 0;      // Alt sýnýr

        buckets[bucketIndex].push_back(arr[i]);
    }

    // 4. ADIM: Her kovayý sýralama ve ana diziye geri yazma
    int index = 0;  
    for (int i = 0; i < n; i++)
    {
        /**
         * Kova içi sýralama için std::sort kullanýlmýþtýr.
         * std::sort, IntroSort implementasyonu sayesinde kova gibi küçük
         * dizilerde otomatik olarak Insertion Sort'a geçer.
         */
        if (!buckets[i].empty()) {
            sort(buckets[i].begin(), buckets[i].end());
            for (float val : buckets[i])
                arr[index++] = val;
        }
    }
}

int main() {
    // Örnek veri seti: Daðýnýk ondalýklý sayýlar
    vector<float> data = {15.5, 1.2, 55.8, 110.0, 10.0, 42.7, 88.3};
    int kovaSayisi = 5;

    cout << "Siralamadan Once: ";
    for (float x : data) cout << x << " ";
    cout << endl;

    bucketSort(data, kovaSayisi);

    cout << "Siralamadan Sonra (Bucket Sort): ";
    for (float x : data) cout << x << " ";
    cout << endl;

    return 0;
}
