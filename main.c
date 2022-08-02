#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
int N;

typedef struct kayit
{
    int ogrNo;
    int dersKodu;
    int puan;
    int offset;

} ogrenci;
typedef struct indeks
{
    int numara;
    int offset;
} kayit;
ogrenci ogrenci1[50];
kayit indeks1[100];
FILE *index;
FILE *data;
FILE *yedek;
FILE *yedek2;

void kayitekle(int adet)
{

    data = fopen("veri.dat", "w+b");
    index = fopen("index.txt", "w+");

    if (data == NULL)
    {
        printf("dosya acilamadi");
    }
    else
    {
        for (int i = 0; i < adet; i++)
        {
            printf("ogrenci no giriniz:");
            scanf("%d", &ogrenci1[i].ogrNo);
            ogrenci1[i].offset = i;

            printf("ders kodunu giriniz:");
            scanf("%d", &ogrenci1[i].dersKodu);

            printf("ogrencinin notunu giriniz:");
            scanf("%d", &ogrenci1[i].puan);
            fwrite(&ogrenci1[i], sizeof(ogrenci), 1, data);
            fprintf(index, "%d %d\n", ogrenci1[i].ogrNo, ogrenci1[i].offset);
        }
    }
    fclose(data);
    fclose(index);
    indeksirala(adet);
}
void indeksirala(int adet)
{
    index = fopen("index.txt", "r+");
    int number;
    int offset;
    int arr1[adet];
    int arr2[adet];
    int b = 0;
    while (!feof(index))
    {
        fscanf(index, "%d %d\n", &number, &offset);

        arr1[b] = number;
        arr2[b] = offset;
        b++;
    }

    for (int i = 0; i < b - 1; i++)
    {
        for (int j = 0; j < b - 1 - i; j++)
        {
            if (arr1[j] > arr1[j + 1])
            {
                int temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;

                int x = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = x;
            }
        }
    }

    fclose(index);
    indeksguncelle(arr1, arr2, adet);
}
void indeksguncelle(int arr1[], int arr2[], int adet)
{
    index = fopen("index.txt", "w");

    for (int i = 0; i < adet; i++)
    {
        fprintf(index, "%d %d\n", arr1[i], arr2[i]);
    }
    fclose(index);
}

void kayitbul()
{
    // birden fazla kaydý bulunanlarý bulmayý yap!!
    int n = 0;
    index = fopen("index.txt", "r");
    data = fopen("veri.dat", "rb");
    int aranan;
    int a = 0;

    printf("aradiginiz ogrencinin numarasini giriniz:");
    scanf("%d", &aranan);

    int offset;
    while (!feof(index))
    {
        fscanf(index, "%d %d", &indeks1[n].numara, &indeks1[n].offset);
        n++;
    }
    for (int i = 0; i < n; i++)
    {

        if (indeks1[i].numara == aranan)
        {
            offset = indeks1[i].offset;
        }
    }
    while (!feof(data))
    {
        fread(&ogrenci1, sizeof(ogrenci), 1, data);
        if (ogrenci1[a].offset == offset)
        {
            printf("ogr no:%d\n ders kodu:%d\n notu:%d\n", ogrenci1[a].ogrNo, ogrenci1[a].dersKodu, ogrenci1[a].puan);
        }
    }
    fclose(index);
    fclose(data);
}
void kayitsil(int adet)
{
    int silinecek;
    int offset;
    int a = 0;
    int durum = 0;
    int n = 0;
    printf("silinecek ogrencinin numarasini giriniz:");
    scanf("%d", &silinecek);
    data = fopen("veri.dat", "rb");
    yedek = fopen("yedek.dat", "wb");
    index = fopen("index.txt", "r");

    while (!feof(index))
    {
        fscanf(index, "%d %d", &indeks1[n].numara, &indeks1[n].offset);
        n++;
    }
    for (int i = 0; i < n; i++)
    {

        if (indeks1[i].numara == silinecek)
        {
            offset = indeks1[i].offset;
        }
    }
    while (!feof(data))
    {
        fread(&ogrenci1, sizeof(ogrenci), 1, data);
        if (ogrenci1[a].offset == offset)
        {
            printf("ogrenci basariyla silindi!! ogr no:%d ders kodu:%d notu:%d\n", ogrenci1[a].ogrNo, ogrenci1[a].dersKodu, ogrenci1[a].puan);
        }
        else
        {

            fwrite(&ogrenci1[a], sizeof(ogrenci), 1, yedek);
        }
    }
    fclose(index);
    fclose(data);
    fclose(yedek);

    remove("veri.dat");
    rename("yedek.dat", "veri.dat");

    remove("yedek.dat");
    indeksyenile(adet, silinecek);
}
void indeksyenile(int adet, int silinecek)
{
    int offset;
    int number;
    index = fopen("index.txt", "r");
    yedek2=fopen("yedek2.txt","w");
    while(!feof(index))
    {
        fscanf(index,"%d %d\n",&number,&offset);
        if(number==silinecek)
        {
            printf("basariyla silindi!!\n");
        }
        else
        {
            fprintf(yedek2,"%d %d\n",number,offset);
        }
    }
    fclose(index);
    fclose(yedek2);
    remove("index.txt");
    rename("yedek2.txt","index.txt");
    remove("yedek2.txt");
    indeksirala(adet-1);
}
void kayitguncelle()
{
     index = fopen("index.txt", "r");
    data = fopen("veri.dat", "rb");
    yedek=fopen("yedek.dat","wb");
    int aranan;
    int a = 0;
    int n=0;
    int derskodu,not;
    int temp1,temp2;

    printf("guncellenecek ogrencinin numarasini giriniz:");
    scanf("%d", &aranan);
    printf("yeni ders kodu:");
    scanf("%d",&derskodu);
    printf("yeni notu giriniz:");
    scanf("%d",&not);


    int offset;
    while (!feof(index))
    {
        fscanf(index, "%d %d", &indeks1[n].numara, &indeks1[n].offset);
        n++;
    }
    for (int i = 0; i < n; i++)
    {

        if (indeks1[i].numara == aranan)
        {
            offset = indeks1[i].offset;
        }
    }
    while (!feof(data))
    {
        fread(&ogrenci1, sizeof(ogrenci), 1, data);
        if (ogrenci1[a].offset == offset)
        {
            temp1=ogrenci1[a].dersKodu;
            temp2=ogrenci1[a].puan;
            ogrenci1[a].dersKodu=derskodu;
            ogrenci1[a].puan=not;
           // printf("ogr no:%d\n ders kodu:%d\n notu:%d\n", ogrenci1[a].ogrNo, ogrenci1[a].dersKodu, ogrenci1[a].puan);
        }
        fwrite(&ogrenci1[a], sizeof(ogrenci), 1, yedek);
    }
    fclose(index);
    fclose(data);
    fclose(yedek);
     remove("veri.dat");
    rename("yedek.dat", "veri.dat");

    remove("yedek.dat");
}

void indeksdosyasigor()
{
    int number;
    int offset;
    index = fopen("index.txt", "r+");
    printf("NUMARA  OFFSET\n");
    if (index != NULL)
    {
        while (!feof(index))
        {

            fscanf(index, "%d %d", &number, &offset);
            printf("%d %d\n", number, offset);
        }
    }
    else
    {
        printf("dosya acilamadi!!");
    }
    fclose(index);
}
void veridosyasinigor()
{

    int ogrno;
    int derskodu;
    int not ;
    data = fopen("veri.dat", "r+b");
    if (data != NULL)
    {
        printf("OGRENCI NO DERS KODU NOTU\n");
        while (!feof(data))
        {

            fread(&ogrenci1, sizeof(ogrenci), 1, data);
            printf("%d %d %d \n", ogrenci1->ogrNo, ogrenci1->dersKodu, ogrenci1->puan);
        }
    }
    else
    {
        printf("dosya bulunamadi!!");
    }
    fclose(data);
}
void indeksdosyasisil()
{
    int result = remove("index.txt");
    if (result == 0)
    {
        printf("dosya silindi!!\n");
    }
    else
    {
        printf("dosya silinemedi!!\n");
    }
}

void secenek(int adet)
{
    printf("ASAGIDAKI SECENEKLERDEN BIRINI SECINIZ:\n"
           "1-Kayit Ekle\n"
           "2-Kayit Bul\n"
           "3-Kayit Sil\n"
           "4-Kayit Guncelle\n"
           "5-Indeks Dosyasini Gor\n"
           "6-Veri Dosyasini Gor\n"
           "7-Indeks Dosyasini Sil\n"
           "0-cikis\n");
    scanf("%d", &N);
    switch (N)
    {
    case 1:
        kayitekle(adet);
        break;
    case 2:
        kayitbul();
        break;
    case 3:
        kayitsil(adet);
        break;
    case 4:
        kayitguncelle();
        break;
    case 5:
        indeksdosyasigor();
        break;
    case 6:
        veridosyasinigor();
        break;
    case 7:
        indeksdosyasisil(adet);
        break;
    }
}

int main()
{
    int adet;
    printf("kac kayit gireceginizi giriniz:");
    scanf("%d", &adet);
    while (1)
    {
        secenek(adet);
    }
    return 0;
}
