#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Hash tablosu boyutu
#define TABLO_BOYUTU 100

// Hash tablosu düğümü
struct HashDugumu {
    int eleman;
    struct HashDugumu* next;
};

// Hash tablosu
struct HashTablosu {
    struct HashDugumu* tablo[TABLO_BOYUTU];
};

// Hash tablosu ve düğümleri için bellekten alan ayırma
struct HashTablosu* hashTablosuOlustur() {
    struct HashTablosu* tablo = (struct HashTablosu*)malloc(sizeof(struct HashTablosu));
    for (int i = 0; i < TABLO_BOYUTU; i++) {
        tablo->tablo[i] = NULL;
    }
    return tablo;
}

// Hash değeri hesaplama
int hashHesapla(int eleman) {
    return eleman % TABLO_BOYUTU;
}

// Hash tablosuna eleman ekleme
void elemanEkle(struct HashTablosu* tablo, int eleman) {
    int hash = hashHesapla(eleman);

    // Yeni bir düğüm oluştur
    struct HashDugumu* yeniDugum = (struct HashDugumu*)malloc(sizeof(struct HashDugumu));
    yeniDugum->eleman = eleman;
    yeniDugum->next = NULL;

    // Hash tablosunda ekleme
    if (tablo->tablo[hash] == NULL) {
        tablo->tablo[hash] = yeniDugum;
    } else {
        // Zincirleme ile ekleme
        struct HashDugumu* temp = tablo->tablo[hash];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = yeniDugum;
    }
}

// Dizideki tekrar eden elemanları bulma
void tekrarEdenleriBul(int dizi[], int boyut) {
    struct HashTablosu* tablo = hashTablosuOlustur();
    bool tekrarEdenVar = false;

    for (int i = 0; i < boyut; i++) {
        int eleman = dizi[i];
        int hash = hashHesapla(eleman);

        struct HashDugumu* temp = tablo->tablo[hash];
        while (temp != NULL) {
            if (temp->eleman == eleman) {
                printf("%d ", eleman);
                tekrarEdenVar = true;
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL) {
            elemanEkle(tablo, eleman);
        }
    }

    if (!tekrarEdenVar) {
        printf("Tekrar eden eleman bulunamadi.");
    }

    printf("\n");

    // Bellekten alanları serbest bırakma
    for (int i = 0; i < TABLO_BOYUTU; i++) {
        struct HashDugumu* temp = tablo->tablo[i];
        while (temp != NULL) {
            struct HashDugumu* silinecek = temp;
            temp = temp->next;
            free(silinecek);
        }
    }
    free(tablo);
}

int main() {
    char elemanlar[100];
    char* eleman;

    printf("Elemanlari aralarina virgul koyarak girin: ");
    scanf("%s", elemanlar);

    int boyut = 0;
    int dizi[100];

    eleman = strtok(elemanlar, ",");
    while (eleman != NULL) {
        int veri = atoi(eleman);
        dizi[boyut++] = veri;
        eleman = strtok(NULL, ",");
    }

    printf("Dizideki tekrar eden elemanlar: ");
    tekrarEdenleriBul(dizi, boyut);

    return 0;
