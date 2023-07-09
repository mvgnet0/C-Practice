#include <stdio.h>

int main() {
    int dizi[100];
    int boyut;

    printf("Dizinin boyutunu girin: ");
    scanf("%d", &boyut);

    printf("Dizinin elemanlarini girin:\n");
    for (int i = 0; i < boyut; i++) {
        printf("Eleman %d: ", i + 1);
        scanf("%d", &dizi[i]);
    }

    int enBuyuk = dizi[0];

    for (int i = 1; i < boyut; i++) {
        if (dizi[i] > enBuyuk) {
            enBuyuk = dizi[i];
        }
    }

    printf("En buyuk sayi: %d\n", enBuyuk);

    return 0;
}
