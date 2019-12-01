#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <string.h>
struct tekne{
	char kayitDurumu;    // Kayit dolu olup olmamasi bilinir. '*' : kayit dolu , '-' : Kayit bos
	int tekne_ID;
	char tekne_ismi[20];
	char liman[20];
	char bandira[20]; 
}tekne;

FILE *dosya,*yedek;
void tekneKaydi(void);
void listele(void); 
void tekneSil(void);
void guncelle(void); 

int main() { 
	char sec;
	do{
    	system("cls");
   		printf("1- Tekne Kaydi\n2- Tekne Listele\n3- Tekne Sil\n4- Tekne Guncelle\n5- Programdan Cik\n\n Yapmak Istediginiz Islemi Seciniz: ");
   		sec=getche();
   		switch(sec){
   			case '1':{ tekneKaydi(); break;}
   			case '2':{ listele(); break;}
   			case '3':{ tekneSil(); break;}
   			case '4':{ guncelle(); break; }
   			case '5':{ exit(0); break; }
   			default:{
			   	printf("\n\n1-5 Arasinda bir islem secebilirsiniz devam etmek icin bir tusa basiniz...");
   				getch(); 
				break;
			}
   		}
	}
	while(sec!=5); 
 	getch();
 	return 0;
}

void tekneKaydi(void){
	char sec;
 	dosya = fopen("Teknelerin_kayitlari.dat","r+b");
 	if( dosya == NULL ){
 		dosya = fopen("Teknelerin_kayitlari.dat","w+b");
    }
 	system("cls");
    printf("tekne id giriniz  : ");
 	scanf("%d",&tekne.tekne_ID);
 	// kontrol etme parcasi  ayni kayit edilmesin 
 	int num =tekne.tekne_ID ;
  	int  boyut = filelength(fileno(dosya)) / sizeof(struct tekne);
   	int i;   
   	for( i=0;i<boyut;i++){
  		fseek(dosya,(i*sizeof(struct tekne)),SEEK_SET);
  		fread(&tekne,sizeof(struct tekne),1,dosya);
  		if(tekne.kayitDurumu == '*' && num == tekne.tekne_ID     ){
    		printf("bu kayidi dosya da vardir ve daha once eklenmistir!!! .");
			getch();
			return ;
  		}
  	} 
     
    tekne.tekne_ID =num ;
  	fflush(stdin);
    printf("tekne Adi: ");
 	gets(tekne.tekne_ismi);
 
 	fflush(stdin);
    printf("teknenin limani: ");
 	gets(tekne.liman);
  
  	fflush(stdin);
    printf("teknenin bandirasi: ");
 	gets(tekne.bandira);
 
 	fflush(stdin);
 	printf("Girilen teknenin bilgiler kayit edilsin mi ? [e/h]");
 	sec = getche();
 	if( sec == 'E' || sec == 'e'){ 
  		tekne.kayitDurumu = '*'; fseek(dosya,filelength(fileno(dosya)),SEEK_SET);
  		fwrite(&tekne,sizeof(struct tekne),1,dosya);}
  
 	else{
	  printf("\n\nBilgiler kayit edilmedi devam etmek icin bir tusa basiniz..."); 
	  getch();
	}
 	fclose(dosya);
 
}

void listele(void){
	int boyut,i;
 	system("cls");
 	dosya = fopen("Teknelerin_kayitlari.dat","r+b");
 	if(dosya == NULL) printf("Dosya acilamadi\n");
 	boyut = filelength(fileno(dosya)) / sizeof(struct tekne);
 	for(i=0;i<boyut;i++){
  		fseek(dosya,(i*sizeof(struct tekne)),SEEK_SET);
  		fread(&tekne,sizeof(struct tekne),1,dosya);
  		if(tekne.kayitDurumu == '*'){
 		printf("----------------------------------------------------------------------------------------\n");
 		printf(" Tekne No\t\tTekne Adi\t\tTekne limani\t\tTekne bandirma \n");
  		printf("  %2d\t\t\t%2s\t\t\t%2s\t\t\t%2s\t\n", tekne.tekne_ID, tekne.tekne_ismi, tekne.liman, tekne.bandira );
		}
	}
 	printf("\nToplam teknelerin kayitlerin sayisi = %d",boyut);
 	printf("\nDevam etmek icin bir tusa basiniz...");
 	fclose(dosya);
 	getch();
}

 

void tekneSil(void){
	int num,durum=0,boyut,i;
 	system("cls");
 	printf("Silinecek  teknenin kaydin numarasini giriniz: ");
 	scanf("%d",&num);
 	system("cls");
 	dosya = fopen("Teknelerin_kayitlari.dat","r+b");
 	yedek = fopen("yedek.dat","w+b");
 	if( dosya == NULL){
  		puts("Dosya acilamadi");
  		exit(1);
	}
 	boyut = filelength(fileno(dosya)) / sizeof(struct tekne);
 	for(i=0;i<boyut;i++){
  		fseek(dosya,(i*sizeof(struct tekne)),SEEK_SET);
  		fread(&tekne,sizeof(struct tekne),1,dosya);
  		if( tekne.tekne_ID != num){
   			fwrite(&tekne,sizeof(struct tekne),1,yedek);
  		}
  		else durum=1;
 	}
 	fclose(dosya);
 	fclose(yedek);
 	if(durum == 1){
  		remove("Teknelerin_kayitlari.dat");
  		rename("yedek.dat","Teknelerin_kayitlari.dat");
  		puts("tekne kaydi silindi devam etmek icin bir tusa basiniz...");
  		getch();
 	}
 	else{
  		remove("yedek.dat");
  		printf("%d numarasinda bir tekne numarasi bulunamadi devam etmek icin bir tusa basin ...",num);
 	}
 	getch();
}

 
void guncelle(void){
 	char sec;
 	int boyut,i,num;
 	system("cls");
 	dosya = fopen("Teknelerin_kayitlari.dat","r+b");
 	if(dosya == NULL) printf("Dosya acilamadi\n");
 	printf("Bilgilerini guncelleyeceginiz teknenin numarasini giriniz: ");
 	scanf("%d",&num);
 	system("cls");
 	boyut = filelength(fileno(dosya)) / sizeof(struct tekne);

 	for(i=0;i<boyut;i++){
  		fseek(dosya,(i*sizeof(struct tekne)),SEEK_SET);
  		fread(&tekne,sizeof(struct tekne),1,dosya);
  		if(tekne.kayitDurumu == '*' && tekne.tekne_ID == num){
    		system("cls");
    		printf("%s isimli teknenin bilgileri degistirilsin mi?[E/H]\n",tekne.tekne_ismi);
    		sec = getche();
   			if( sec == 'E' || sec == 'e'){
    			system("cls");
				
				printf("tekne Adi: ");
				fflush(stdin);
				gets(tekne.tekne_ismi);
				fflush(stdin);
				printf("\nteknenin limani: ");
				gets(tekne.liman);
				fflush(stdin);
  
				printf("\nteknenin bandirasi: ");
				gets(tekne.bandira);
				fflush(stdin);
  
  				fseek(dosya,(i*sizeof(struct tekne)),SEEK_SET);
  				fwrite(&tekne,sizeof(struct tekne),1,dosya);
     		}
     		else{
  				printf("\n\ntekne kaydi degistirilmedi.");
     		}
  		}
 	}
 	fclose(dosya);
 	printf("Olye bir id bulunmadi\nDevam etmek icin bir tusa basiniz...");
 	getch();
}
