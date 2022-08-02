#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
int N;

struct kayit{
int ogrNo;
int dersKodu;
int puan;
};
void kayitekle()
{

}
void kayitbul()
{

}
void kayitsil()
{

}
 void kayitguncelle()
 {

 }
 void ındeksdosyasigor()
 {

 }
 void veridosyasinigor()
 {

 }
 void ındeksdosyasisil()
 {
printf("dsfşldmf");
 }

void secenek()
{
printf("ASAGIDAKI SECENEKLERDEN BIRINI SECINIZ:/n 1-Kayit Ekle/n 2-Kayit Bul/n 3-Kayit Sil/n 4-Kayit Güncelle/n 5-Indeks Dosyasini Gor/n 6-Veri Dosyasini Gor/n 7-Indeks Dosyasini Sil/n");
scanf("%d",&N);
switch(N){
case 1:
kayitekle();
break;
case 2:
kayitbul();
break;
case 3:
kayitsil();
break;
case 4:
kayitguncelle();
break;
case 5:
ındeksdosyasigor();
break;
case 6:
veridosyasinigor();
break;
case 7:
ındeksdosyasisil();}
}


int main()
{


secenek();

    return 0;
}