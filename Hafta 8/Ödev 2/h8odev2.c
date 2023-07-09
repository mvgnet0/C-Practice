#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bağlı liste düğümü yapısı
struct Node {
    int data;
    struct Node* next;
};

// Yeni bir düğüm oluşturma
struct Node* yeniDugum(int veri) {
    struct Node* dugum = (struct Node*)malloc(sizeof(struct Node));
    dugum->data = veri;
    dugum->next = NULL;
    return dugum;
}

// Bağlı listeye eleman ekleme
void listeEkle(struct Node** baslangic, int veri) {
    struct Node* dugum = yeniDugum(veri);

    // Boş liste ise
    if (*baslangic == NULL) {
        *baslangic = dugum;
        return;
    }

    // Listenin sonuna kadar ilerle
    struct Node* temp = *baslangic;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Yeni düğümü listenin sonuna ekle
    temp->next = dugum;
}

// Bağlı listeyi gezerek eleman sayısını bulma
int elemanSayisi(struct Node* baslangic) {
    int sayac = 0;
    struct Node* temp = baslangic;

    while (temp != NULL) {
        sayac++;
        temp = temp->next;
    }

    return sayac;
}

// Bağlı listeyi yazdırma
void listeYazdir(struct Node* baslangic) {
    struct Node* temp = baslangic;

    while (temp != NULL) {
        printf("%d", temp->data);

        if (temp->next != NULL) {
            printf(", ");
        }

        temp = temp->next;
    }

    printf("\n");
}

int main() {
    struct Node* baslangic = NULL;
    char elemanlar[100];
    char* eleman;

    printf("Elemanlari aralarina virgul koyarak girin: ");
    scanf("%s", elemanlar);

    eleman = strtok(elemanlar, ",");
    while (eleman != NULL) {
        int veri = atoi(eleman);
        listeEkle(&baslangic, veri);
        eleman = strtok(NULL, ",");
    }

    printf("Bağlı liste: ");
    listeYazdir(baslangic);

    int elemanlarSayisi = elemanSayisi(baslangic);
    printf("Eleman sayisi: %d\n", elemanlarSayisi);

    return 0;
}
