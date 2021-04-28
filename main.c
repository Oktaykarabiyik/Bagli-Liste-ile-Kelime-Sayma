#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char *data;
    int adet;
    struct node *next;
    struct node *prev;

};
struct node *ilk=NULL,*son=NULL;
void sonaekle(char *a,int kelimesayisi)
{
    struct node *yeni=(struct node*) malloc(sizeof(struct node));
    yeni->data=(char*)malloc((strlen(a))+1);
    yeni->adet=kelimesayisi;
    strcpy(yeni->data,a);
    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->next=NULL;
        ilk->prev=NULL;
    }
    else
    {
        yeni->prev=son;
        son->next=yeni;
        yeni->next=NULL;
        son=yeni;
    }
}
int AraVarMi(char *x)
{
    struct node *ara=ilk;
    int kontrol=1;

    if(ilk==NULL)
    {
        kontrol=1;
    }
    else
    {
        while(ara!=NULL)
        {

            if(strcmp(ara->data,x)==0)
                kontrol=0;
            ara=ara->next;
        }
    }
    if(kontrol==1)
        return 1;

    else
        return 0;
}
void basaekle(char *a,int kelimesayisi)
{
    struct node *yeni=(struct node*) malloc(sizeof(struct node));
    yeni->data=(char*)malloc((strlen(a))+1);
    yeni->adet=kelimesayisi;
    strcpy(yeni->data,a);
    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->next=NULL;
        ilk->prev=NULL;
    }
    else
    {
        ilk->prev=yeni;
        yeni->next=ilk;
        yeni->prev=NULL;
        ilk=yeni;
    }
}
void Listele()
{
    struct node *dolas=ilk;
    while(dolas!=NULL)
    {
        printf("%s:%d\n",dolas->data,dolas->adet);
        dolas=dolas->next;
    }
}
void ArayaEkle(int *a,int kelimesayisi,struct node *insert)
{
    struct node *yeni=(struct node*) malloc(sizeof(struct node));

    yeni->data=(char*)malloc((strlen(a))+1);
    yeni->adet=kelimesayisi;
    strcpy(yeni->data,a);
    yeni->prev=insert;
    yeni->next=insert->next;
    insert->next->prev=yeni;
    insert->next=yeni;

}
void SiraliEkle(char *a,int kelimesayisi)
{
    if(ilk==NULL)
    {basaekle(a,kelimesayisi);
    }
    else
    {
        struct node *insert;
        insert=son;
        while(insert->adet<kelimesayisi)
        {
            if(insert==ilk)
            {
                basaekle(a,kelimesayisi);
                return;
            }

            insert=insert->prev;
        }
        if(insert==son)
        {
            sonaekle(a,kelimesayisi);
        }
        else
            ArayaEkle(a,kelimesayisi,insert);
    }
}

int main()
{
    FILE *dosya;
    char *a=(char*)malloc(1000*sizeof(char));
    char *b=(char*)malloc(1000*sizeof(char));
    char karakter='x';
    char karakter2='y';
    char karakter3='z';
    int sayac=0;
    int sayac1=0;
    int sayac2=0;
    int bosluk=0;
    int bosluk2=1;
    int harfsayisi=1;
    int kelimesayisi=1;
    if((dosya=fopen("metin.txt","r"))!=NULL)
    {
        while(karakter!=EOF)
        {
            while(bosluk==0)
            {
                karakter=fgetc(dosya);
                sayac++;
                sayac1++;
                if(karakter==' ' || karakter==EOF || karakter=='\n')
                {
                    fseek(dosya, 0, SEEK_SET);
                    fgets(a,sayac,dosya);
                    bosluk++;
                    while(karakter!=EOF)
                    {
                        if((karakter==' ' || karakter==EOF || karakter=='\n') && bosluk2>0 )
                        {

                            fseek(dosya,sayac1,SEEK_SET);
                            karakter=fgetc(dosya);
                            while(karakter!=' ' && karakter!=EOF && karakter!='\n')
                            {
                                harfsayisi++;
                                karakter=fgetc(dosya);

                            }
                            fseek(dosya,sayac1,SEEK_SET);
                            fgets(b,harfsayisi,dosya);
                            if(strcmp(a,b)==0)
                                kelimesayisi++;

                            sayac1=sayac1+harfsayisi;
                            harfsayisi=1;
                        }
                    }
                     SiraliEkle(a,kelimesayisi);

                }
            }
            kelimesayisi=1;
            while(karakter2!=EOF)
            {
                if(bosluk>0)
                {

                    fseek(dosya,sayac,SEEK_SET);
                    karakter2=fgetc(dosya);
                    while(karakter2!=' ' && karakter2!=EOF && karakter2!='\n')
                    {
                        harfsayisi++;
                        karakter2=fgetc(dosya);

                    }
                    fseek(dosya,sayac,SEEK_SET);
                    fgets(a,harfsayisi,dosya);

                    sayac=sayac+harfsayisi;
                    sayac2=sayac;
                    harfsayisi=1;
                    karakter3=karakter2;
                    while(karakter3!=EOF)
                    {
                            fseek(dosya,sayac2,SEEK_SET);
                            karakter3=fgetc(dosya);
                            while(karakter3!=' ' && karakter3!=EOF && karakter3!='\n')
                            {
                                harfsayisi++;
                                karakter3=fgetc(dosya);
                            }
                            fseek(dosya,sayac2,SEEK_SET);
                            fgets(b,harfsayisi,dosya);
                            if(strcmp(a,b)==0)
                                kelimesayisi++;

                            sayac2=sayac2+harfsayisi;
                            harfsayisi=1;

                    }
                    if(AraVarMi(a)==1)
                    {
                        SiraliEkle(a,kelimesayisi);
                    }

                    kelimesayisi=1;
                }
            }

        }
        printf("BAGLI LISTE:\n");
        Listele();

    }
    else
        printf("Dosya bulunamadi");
    return 0;
}
