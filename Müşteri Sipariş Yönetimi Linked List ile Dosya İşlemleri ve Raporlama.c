#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Musteri {
    char siparisKodu[5];
    char musteriId[5];
    char musteriAdi[50];
    char urunTipi[50];
    char siparisGunu[20];
    struct Musteri *next; 
};


void dosyadanOku(const char *dosyaAdi, struct Musteri **baslangic) {
    FILE *dosya = fopen(dosyaAdi, "r");

    struct Musteri *temp, *sonraki;
    temp = (struct Musteri *)malloc(sizeof(struct Musteri));

    while (fscanf(dosya, "%4s %4s %49s %49s %19s",
                  temp->siparisKodu, temp->musteriId,
                  temp->musteriAdi, temp->urunTipi,
                  temp->siparisGunu) == 5) {

        temp->next = NULL;

        if (*baslangic == NULL) {
            *baslangic = temp;
        } else {
            sonraki = *baslangic;
            while (sonraki->next != NULL) {
                sonraki = sonraki->next;
            }
            sonraki->next = temp;
        }

        temp = (struct Musteri *)malloc(sizeof(struct Musteri));
    }

    fclose(dosya);
}

void ekranaYazdir(struct Musteri *baslangic) {
    while (baslangic != NULL) {
        printf("%s %s %s %s %s\n", baslangic->siparisKodu, baslangic->musteriId,
               baslangic->musteriAdi, baslangic->urunTipi,
               baslangic->siparisGunu);
        baslangic = baslangic->next;
    }
}


void siparisBilgisiDosyaYaz(struct Musteri *baslangic) {
    while (baslangic != NULL) {
        FILE *dosya;
        char dosyaAdi[20];
        sprintf(dosyaAdi, "%s.txt", baslangic->musteriAdi);
        dosya = fopen(dosyaAdi, "w");
        fprintf(dosya, "Merhaba %s, %s gunu tarafinizdan siparis numarasi %s olan musteri id %s olan %s alisverisi gerceklestirilmistir\n",
                baslangic->musteriAdi, baslangic->siparisGunu,
                baslangic->siparisKodu, baslangic->musteriId,
                baslangic->urunTipi);
        fclose(dosya);
        baslangic = baslangic->next;
    }
}

void genelRaporOlustur(struct Musteri *baslangic) {
    int pantolonSayisi = 0, kazakSayisi = 0, kabanSayisi = 0;

    while (baslangic != NULL) {
        if (strcmp(baslangic->urunTipi, "Pantolon") == 0) {
            pantolonSayisi++;
        } else if (strcmp(baslangic->urunTipi, "Kazak") == 0) {
            kazakSayisi++;
        } else if (strcmp(baslangic->urunTipi, "Kaban") == 0) {
            kabanSayisi++;
        }
        baslangic = baslangic->next;
    }

    FILE *raporDosya = fopen("rapor.txt", "w");

    fprintf(raporDosya, "Pantolon siparis sayisi: %d\nKazak siparis sayisi: %d\nKaban siparis sayisi: %d\n",
            pantolonSayisi, kazakSayisi, kabanSayisi);
    fclose(raporDosya);
}

void listeTemizle(struct Musteri *baslangic) {
    struct Musteri *gecici;
    while (baslangic != NULL) {
        gecici = baslangic;
        baslangic = baslangic->next;
        free(gecici);
    }
}

int main() {
    struct Musteri *baslangic = NULL;

    dosyadanOku("input.txt", &baslangic);

    printf("Linked List:\n");
    ekranaYazdir(baslangic);

    siparisBilgisiDosyaYaz(baslangic);

    genelRaporOlustur(baslangic);

    listeTemizle(baslangic);

    return 0;
}

