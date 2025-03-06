#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


struct kontrol
{
    int satir;
    int sutun;
    int acik;
    int acilan;
    int bitti;
};
int boyut;
void ardisik(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut],struct kontrol d[boyut][boyut],int satir ,int sutun,int zorluk);
void mayin(int gercek_dizi[boyut][boyut],int zorluk,struct kontrol d[boyut][boyut]);
void ortam_yildiz(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut],int satir,int sutun,struct kontrol d[boyut][boyut]);
void ortam_sayi(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut],int satir,int sutun);
void deger(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]);
void bayrak(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]);
void yazdir(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]);
void bayrak_sil(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]);




int main()
{
    
    printf("oyun alanini boyutunu belirleyin (ornegin 9*9 icin 9 girin): ");scanf("%d",&boyut);
    while (!(boyut <15 && boyut > 0)){
        printf("\nhatali deger girdiniz lutfen gecerli bir zorluk degeri giriniz:");scanf("%d",&boyut);
        while (getchar() != '\n');
    }
    struct kontrol d[boyut][boyut];
    char ilk_dizi[boyut][boyut];
    int gercek_dizi[boyut][boyut];
    int zorluk;
    d[0][0].bitti=0;
    d[0][0].acilan=0;
    printf("oyunun zorluk seviyesi ne olsun (1-9):");scanf("%d",&zorluk);
    while (!(zorluk <10 && zorluk > 0)){
        printf("hatali deger girdiniz lutfen gecerli bir zorluk degeri giriniz:");scanf("%d",&zorluk);
        while (getchar() != '\n');
    }
    

    memset(ilk_dizi, '*',sizeof(ilk_dizi));
    memset(gercek_dizi, 0,sizeof(gercek_dizi));
    memset(d, 0,sizeof(d));
    mayin(gercek_dizi,zorluk,d);
    deger(ilk_dizi,gercek_dizi);
    int satir=-1,sutun=-1,devam=1,islem;
    puts("");
    puts("");
    printf("%d adet mayin var\n",d[0][0].bitti);
   
    do
    {
        if(gercek_dizi[satir-1][sutun-1]==-1){
            memset(ilk_dizi, '*',sizeof(ilk_dizi));
            memset(gercek_dizi, 0,sizeof(gercek_dizi));
            memset(d, 0,sizeof(d));
            mayin(gercek_dizi,zorluk,d);
            deger(ilk_dizi,gercek_dizi);
        }
        if(devam==2){
            printf("oyunun zorluk seviyesi ne olsun (1-9)");scanf("%d",&zorluk);
            while (!(zorluk <10 && zorluk > 0)){
                printf("hatali deger girdiniz lutfen gecerli bir zorluk degeri giriniz:");scanf("%d",&zorluk);
                while (getchar() != '\n');            
            }
            mayin(gercek_dizi,zorluk,d);
            deger(ilk_dizi,gercek_dizi);
        }
        puts("");
        ortam_yildiz(ilk_dizi,gercek_dizi,satir,sutun,d);   
        
        puts("1 --- kutu ac");
        puts("2 --- bayrak koy");
        puts("3 --- bayrak kaldir");
        printf("yapmak istediginiz islemi secin ");
       
        scanf("%d",&islem);
        while (!(islem <4 && islem > 0)){
            printf("hatali deger girdiniz lutfen gecerli bir degeri giriniz:");scanf("%d",&islem);
            while (getchar() != '\n');            
        }
        switch (islem)
        {
            case 1 :      
                printf("satir giriniz (1-%d) :",boyut);scanf("%d",&satir);
                while (!(satir <boyut+1 && satir > 0)){
                    if(gercek_dizi[satir][sutun])
                    printf("hatali deger girdiniz lutfen gecerli bir satir degeri giriniz:");scanf("%d",&satir);
                    while (getchar() != '\n');            
                }
                printf("sutun giriniz (1-%d) :",boyut);scanf("%d",&sutun);
                while (!(sutun <boyut+1 && sutun > 0)){
                    printf("hatali deger girdiniz lutfen gecerli bir sutun degeri giriniz:");scanf("%d",&sutun);
                    while (getchar() != '\n');            
                }
                
                ardisik(ilk_dizi,gercek_dizi,d,satir,sutun,zorluk);
                break;
            case 2 :
                bayrak(ilk_dizi,gercek_dizi);
                break;
            case 3 :
               
                bayrak_sil(ilk_dizi,gercek_dizi);
                break;
            case 4 :
                yazdir(ilk_dizi,gercek_dizi);
                break;
            default:
                break;
        }
        if(gercek_dizi[satir-1][sutun-1]==-1)
        {
            int puan=100*(d[0][0].acilan/((boyut*boyut)-(d[0][0].bitti)));
            puts("");
            puts("");
            puts("");
            puts("OYUN BITTI...");
            printf("PUANINIZ :%d",puan) ;
            puts("");
            ortam_sayi(ilk_dizi,gercek_dizi,satir,sutun);
            
            puts("0--oyunu bitir");
            puts("1--oyuna devam et ");
         
            printf("yapmak istediginiz islemi secin ");
           
            scanf("%d",&devam);
            while (!(devam <2 && devam >= 0)){
                printf("hatali deger girdiniz lutfen gecerli bir deger giriniz:");scanf("%d",&devam);
                while (getchar() != '\n');            
            }
            if(devam == 1 ){
                continue;
            }
            break;    
        }

    } while (!(devam==0 || d[0][0].bitti==81-d[0][0].acilan)  );
    {
        if(d[0][0].bitti==81-d[0][0].acilan){
            puts("TEBRIKLER OYUNU KAZANDINIZ");
        }
        puts("OYUN TAMAMLANDI...");   
    }
    return 0;
}



void ortam_yildiz(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut], int satir,int sutun,struct kontrol d[boyut][boyut]){
    for(int i = 1 ; i <= boyut ; i++){
        printf("  %d",i);
    }
    puts("");
    for(int i = 1 ; i <= boyut ; i++){
        printf("___");
    }
    puts("");
    for(int i = 0 ; i < boyut; i++){
        for(int k = 0 ; k < boyut ; k++){
        
            if( d[i][k].acik==1)
            printf("  %d",gercek_dizi[i][k]);
            else
            printf("  %c",ilk_dizi[i][k]);

        }
        printf("| %d\n",i+1);
    }  
}



void ortam_sayi(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut], int satir,int sutun){
    for(int i = 1 ; i <= boyut ; i++){
        printf("  %d",i);
    }
    puts("");
    for(int i = 1 ; i <= boyut; i++){
        printf("___");
    }
    puts("");
    for(int i = 0 ; i < boyut; i++){
        for(int k = 0 ; k < boyut ; k++){
            if(gercek_dizi[i][k]==-1)
            {
                printf(" %d",gercek_dizi[i][k]);
            }
            else
            { 
                printf("  %d",gercek_dizi[i][k]);
            }
          
        }
        printf("| %d\n",i+1);
    }  
}




void mayin(int gercek_dizi[boyut][boyut],int zorluk,struct kontrol d[boyut][boyut]){
    int sayi;
    srand(time(NULL));
    for(int i = 0 ; i < boyut ; i++){
        for(int j = 0 ; j <boyut ;j++ ){
           
            
            sayi=rand() % (11-zorluk);
            if(sayi==0){
                gercek_dizi[i][j]=-1;
                d[0][0].bitti++;
            }
          
        }
    }
}





void deger(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]){
    for(int i = 0 ; i< boyut ; i++){
        for(int j = 0; j < boyut ; j++){
        
            if(gercek_dizi[i-1][j-1]==-1 && i>=1 && j>=1 && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
           
            if(gercek_dizi[i][j-1]==-1 && j>=1 && gercek_dizi[i][j]!=-1 ){
                gercek_dizi[i][j]++;
            }
         
            if(gercek_dizi[i-1][j+1]==-1 && i>=1 && j<=boyut-1 && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
           
            if(gercek_dizi[i][j+1]==-1  && j<=boyut-1 && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
          
            if(gercek_dizi[i+1][j]==-1 && i<=boyut-1 && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
           
            if(gercek_dizi[i+1][j+1]==-1 && j<=boyut-1 && i<=boyut-1 && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
            
            if(gercek_dizi[i-1][j]==-1 && i>=1  && gercek_dizi[i][j]!=-1){
                gercek_dizi[i][j]++;
            }
         
            if(gercek_dizi[i+1][j-1]==-1 && j<=boyut-1 && i>=0 && gercek_dizi[i][j]!=-1 ){
                gercek_dizi[i][j]++;
            }
             
        }
    }
}



void bayrak(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]){
        int satir,sutun;
        printf("satir giriniz (1-%d) :",boyut);scanf("%d",&satir);
        while (!(satir <boyut && satir > 0)){
        printf("hatali deger girdiniz lutfen gecerli bir satir degeri giriniz:");scanf("%d",&satir);
            while (getchar() != '\n');            
        }
        printf("sutun giriniz (1-%d) :",boyut);scanf("%d",&sutun);
        while (!(sutun <boyut && sutun > 0)){
            printf("hatali deger girdiniz lutfen gecerli bir sutun degeri giriniz:");scanf("%d",&sutun);
            while (getchar() != '\n');            
        }
        ilk_dizi[satir-1][sutun-1]='B';
}




void yazdir(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut])
{  for(int i = 1 ; i < 10 ; i++){
        printf("  %d",i);
    }
    puts("");
    for(int i = 1 ; i < 10 ; i++){
        printf("___");
    }
    puts("");
    for(int i = 0 ; i < boyut; i++){
        for(int k = 0 ; k < boyut ; k++){
            if(gercek_dizi[i][k]==-1)
            {
                printf(" %d",gercek_dizi[i][k]);
            }
            else
            { 
                printf("  %d",gercek_dizi[i][k]);
            }
           
        }
        printf("| %d\n",i+1);
    } 

}



void bayrak_sil(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut]){
    int b_satir,b_sutun;
    printf("satir giriniz (1-%d)",boyut);scanf("%d",&b_satir);
    while (!(b_satir <10 && b_satir > 0)){
        printf("hatali deger girdiniz lutfen gecerli bir satir degeri giriniz:");scanf("%d",&b_satir);
        while (getchar() != '\n');            
    }
    printf("sutun giriniz (1-%d)",boyut);scanf("%d",&b_sutun);
    while (!(b_sutun <10 && b_sutun > 0)){
        printf("hatali deger girdiniz lutfen gecerli bir sutun degeri giriniz:");scanf("%d",&b_sutun);
        while (getchar() != '\n');            
    }

    if(ilk_dizi[b_satir-1][b_sutun-1]=='B'){
        ilk_dizi[b_satir-1][b_sutun-1]='*';
    }
    else
    printf("hatali kare sectiniz");
}



void ardisik(char ilk_dizi[boyut][boyut],int gercek_dizi[boyut][boyut],struct kontrol d[boyut][boyut],int satir ,int sutun,int zorluk){
    for(int i = 0; i <  5 ; i++){
        int a_sutun =sutun ;        
        int a_satir =satir ;        
        int sayi=rand()% (10-zorluk);
        int a=0;
        switch (i)
        {
        case 0:
            while (a++ <= sayi)
            {
                if(gercek_dizi[a_satir-1][a_sutun-1]!=-1 && a_satir>1)
                {
                    d[a_satir-1][a_sutun-1].acik=1;
                    a_satir--;
                    d[0][0].acilan++; 
                }  
               
            }
            break;
        case 1:
            while (a++ <= sayi)
            {
                if(gercek_dizi[a_satir-1][a_sutun-1]!=-1 && a_satir<=8)
               { 
                    d[a_satir-1][a_sutun-1].acik=1;
                    a_satir++;
                    d[0][0].acilan++;   
                }
                
            }
            break;
        case 2:
            while (a++ <= sayi)
            {
                if(gercek_dizi[a_satir-1][a_sutun-1]!=-1 && a_sutun<=8)
                {
                    d[a_satir-1][a_sutun-1].acik=1;
                    a_sutun++;
                    d[0][0].acilan++;   
                }
               
            }
            break;
        case 3:
            while (a++ <= sayi)
            {
                if(gercek_dizi[a_satir-1][a_sutun-1]!=-1 &&  a_sutun >1)
                {
                    d[a_satir-1][a_sutun-1].acik=1;
                    a_sutun--;
                    d[0][0].acilan++;   
                }
               
            }
            break;
        case 4:
            d[satir-1][sutun-1].acik=1;
            break;
        }
    }
}
