#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KELIME_UZUNLUK 100

// Trie düğümü yapısı
struct TrieDugumu {
    bool sonKelime; // Kelimenin sonu mu?
    struct TrieDugumu* harfler[26]; // İngiliz alfabesindeki harfler için 26 elemanlı dizi
};

// Yeni bir Trie düğümü oluşturma
struct TrieDugumu* yeniTrieDugumu() {
    struct TrieDugumu* dugum = (struct TrieDugumu*)malloc(sizeof(struct TrieDugumu));
    dugum->sonKelime = false;
    for (int i = 0; i < 26; i++) {
        dugum->harfler[i] = NULL;
    }
    return dugum;
}

// Trie veri yapısına kelime ekleme
void kelimeEkle(struct TrieDugumu* root, const char* kelime) {
    int uzunluk = strlen(kelime);
    struct TrieDugumu* temp = root;

    for (int i = 0; i < uzunluk; i++) {
        int indeks = kelime[i] - 'a'; // İndeks hesaplama

        if (temp->harfler[indeks] == NULL) {
            temp->harfler[indeks] = yeniTrieDugumu();
        }

        temp = temp->harfler[indeks];
    }

    temp->sonKelime = true;
}

// Trie veri yapısında belirli bir metinden başlayan kelimeleri bulma
void kelimeBul(struct TrieDugumu* root, const char* metin, char* prefix, int pozisyon) {
    if (root == NULL) {
        return;
    }

    // Son kelime ise, prefix'i ekrana yazdır
    if (root->sonKelime == true && pozisyon == strlen(metin)) {
        printf("%s\n", prefix);
    }

    // Tüm harfleri kontrol et
    for (int i = 0; i < 26; i++) {
        if (root->harfler[i] != NULL) {
            char yeniPrefix[MAX_KELIME_UZUNLUK];
            sprintf(yeniPrefix, "%s%c", prefix, 'a' + i); // Yeni prefix oluşturma

            kelimeBul(root->harfler[i], metin, yeniPrefix, pozisyon);
        }
    }

    // Metin bitmediyse ve mevcut düğüm metindeki karaktere eşitse devam et
    if (pozisyon < strlen(metin) && root->harfler[metin[pozisyon] - 'a'] != NULL) {
        char yeniPrefix[MAX_KELIME_UZUNLUK];
        sprintf(yeniPrefix, "%s%c", prefix, metin[pozisyon]); // Yeni prefix oluşturma

        kelimeBul(root->harfler[metin[pozisyon] - 'a'], metin, yeniPrefix, pozisyon + 1);
    }
}

int main() {
    struct TrieDugumu* root = yeniTrieDugumu();

    int kelimeSayisi;
    printf("Metin listesindeki kelime sayisini girin: ");
    scanf("%d", &kelimeSayisi);
    getchar(); // Boş karakteri okumak için

    printf("Metin listesindeki kelimeleri girin:\n");
    for (int i = 0; i < kelimeSayisi; i++) {
        char kelime[MAX_KELIME_UZUNLUK];
        fgets(kelime, MAX_KELIME_UZUNLUK, stdin);
        kelime[strcspn(kelime, "\n")] = '\0'; // Yeni satır karakterini kaldır

        kelimeEkle(root, kelime);
    }

    char metin[MAX_KELIME_UZUNLUK];
    printf("Bir metin girin: ");
    fgets(metin, MAX_KELIME_UZUNLUK, stdin);
    metin[strcspn(metin, "\n")] = '\0'; // Yeni satır karakterini kaldır

    printf("'%s' ile baslayan kelimeler:\n", metin);
    kelimeBul(root, metin, "", 0);

    return 0;
}
