# Bucket Sort — Kova Sıralaması

C++ ile geliştirilmiş Bucket Sort implementasyonu. Klasik anlatımlardan farklı
olarak girdinin `[0, 1)` aralığında olduğunu varsaymıyor; dizideki minimum ve
maksimum değerleri bulup normalizasyon yaparak herhangi bir aralıktaki ondalıklı
sayılarla çalışıyor.

İTÜ Matematik Mühendisliği MAT226 Veri Yapıları dersi proje ödevi

## Ekip

Beş kişilik bir ekiple geliştirildi. Takım kaptanı olarak görev aldım;
sorumluluğum ekip koordinasyonu, iş dağılımı ve algoritmanın doğrulanmasıydı.

Ekip arkadaşlarımın isimleri, kişisel bilgi paylaşımından kaçınmak için
belirtilmemiştir.

## Algoritma

Bucket Sort, elemanları değer aralıklarına göre "kova"lara dağıtıp her kovayı
ayrı ayrı sıralayan, sonra kovaları sırayla birleştiren bir dağıtım tabanlı
sıralama algoritmasıdır.

Uygulama dört adımda ilerliyor:

1. **Aralık tespiti.** Dizideki minimum ve maksimum değer tek geçişte bulunur.
2. **Kova oluşturma.** İstenen sayıda boş kova hazırlanır.
3. **Dağıtım.** Her eleman normalizasyon formülüyle bir kovaya yerleştirilir:

   ```
   bucketIndex = (x - minVal) × (n - 1) / range
   ```

   Bu formül her elemanı `[0, n-1]` aralığına eşler; minimum değer daima ilk
   kovaya, maksimum değer son kovaya düşer.
4. **Kova içi sıralama ve birleştirme.** Her kova `std::sort` ile sıralanıp
   sonuçlar sırayla ana diziye yazılır.

## Tasarım kararları

**Aralık bağımsızlığı.** Normalizasyon sayesinde algoritma yalnızca `[0, 1)`
değil, herhangi bir sayı aralığıyla çalışabiliyor.

**Kova içi sıralama tercihi.** `std::sort` kullanıldı. Standart kütüphanenin
IntroSort implementasyonu, kova gibi küçük diziler söz konusu olduğunda
otomatik olarak Insertion Sort'a geçtiği için bu boyutta ayrıca elle Insertion
Sort yazmaya gerek kalmıyor.

**Kenar durumlar.** Boş dizi ve geçersiz kova sayısı başta yakalanıyor. Tüm
elemanlar eşitse `range` sıfır olacağı ve sıfıra bölme hatası doğacağı için
fonksiyon erken çıkıyor. Kayan nokta hassasiyetinden doğabilecek taşmalara karşı
kova indeksi `[0, n-1]` aralığına sabitleniyor.

## Karmaşıklık

| Durum | Zaman | Açıklama |
|---|---|---|
| En iyi / ortalama | O(n + k) | Elemanlar kovalara dengeli dağıldığında |
| En kötü | O(n log n) | Tüm elemanlar tek kovaya düştüğünde |
| Alan | O(n + k) | k kova ve toplam n eleman |

Performans, verinin dağılımına doğrudan bağlı. Düzgün dağılmış veride
karşılaştırma tabanlı algoritmaların O(n log n) sınırının altına inebiliyor;
kümelenmiş veride ise kova içi sıralamanın karmaşıklığına geriliyor.

## Derleme ve çalıştırma

```bash
g++ bucket_sort.cpp -o bucket_sort
./bucket_sort
```

Örnek çıktı:

```
Siralamadan Once: 15.5 1.2 55.8 110 10 42.7 88.3
Siralamadan Sonra (Bucket Sort): 1.2 10 15.5 42.7 55.8 88.3 110
```