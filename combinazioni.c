#include<stdlib.h>
#include<stdio.h>

#define TOT 2000

#include "types.h"
#include "output.h"
#include "test.h"
#include "prematch.h"
#include "match.h"

//Funzioni combinazioni
int cartaAlta(Carta mano[])
{
    int max=0,i;
    for(i=0;i<7;i++){
        if(mano[i].valore>max)
            max=mano[i].valore;
    }
    return max;
}

int coppia(Carta mano[])
{
    int i,j;
    int max=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore>max){
                max=mano[i].valore;
            }
        }
    }
    return max;
}

int doppiaCoppia(Carta mano[])
{
    int c1=0,c2=0,aux,i,j;
    if(coppia(mano)){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore>c2 && mano[i].valore!=c1){
                    c2=mano[i].valore; //Inserisce una coppia in c2 se ha il valore maggiore del suo e diverso da c1
                    if(c2>c1){
                        aux=c2;
                        c2=c1;
                        c1=aux;  //Scambia c2 con c1 se è maggiore di quest'ultimo
                    }
                }
            }
        }
    }
    if(c1==0 || c2==0)
        return 0;
    else
        return c1*1000 + c2*10; //La coppia più alta è determinante
}
int tris(Carta mano[])
{
    int i,j,k,max=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(k=0;k<7;k++){
                if(mano[i].valore==mano[j].valore && mano[j].valore==mano[k].valore && i!=j && j!=k && k!=i && mano[i].valore>max)
                    max=mano[i].valore;
            }
        }
    }
    return max;
}

//Inizio scala
int trovaCarta(Carta mano[], int val)
{
    int i;
    for(i=0;i<7;i++){
        if(mano[i].valore==14 && val==1)
            return 1;
        if(mano[i].valore==val && val!=1)
            return 1;
    }
    return 0;
}

void swap(Carta * c1, Carta * c2)
{
    Carta aux;
    aux.valore=c1->valore;
    c1->valore=c2->valore;
    c2->valore=aux.valore;
    aux.seme=c1->seme;
    c1->seme=c2->seme;
    c2->seme=aux.seme;
    aux.nome=c1->nome;
    c1->nome=c2->nome;
    c2->nome=aux.nome;
}

void sort(Carta mano[]) //BubbleSort
{
    int i,j;
    for(i=0;i<6;i++){
        for(j=6;j>i;j--)
            if(mano[j].valore > mano[j-1].valore)
                swap(&mano[j],&mano[j-1]);
    }
}

int scala(Carta mano[])
{
    int i=0,status=0; //i posizione nell'array
    sort(mano);       //Per selezionare la scala maggiore si fa riferimento a carte ordinate dal valore maggiore al minore
    while(i<7 && status<4){
        if(trovaCarta(mano, mano[i].valore - status) == 1)
            status++;
        else{
            status=0;
            i++;
        }
    }
    if(status==4) //Quando status (completamento scala) arriva a 4 si ritorna il valore della scala (carta più alta)
        return mano[i].valore;
    else
        return 0;
}
//Fine scala

int colore(Carta mano[])
{
    int i,cp=0,cf=0,cc=0,cq=0,max=0;
    for(i=0;i<7;i++){
        if(mano[i].seme==6)
            cp++;
        if(mano[i].seme==5)
            cf++;
        if(mano[i].seme==3)
            cc++;
        if(mano[i].seme==4)
            cq++;
    }
    if(cp>4 && cf<5 && cq<5 && cc<5){
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme==6)
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return max;
    }
    if(cf>4 && cq<5 && cc<5){
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme==5)
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 100+max;
    }
    if(cq>4 && cc<5){
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme==4)
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 200+max;
    }
    if(cc>4){
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme==3)
                max=mano[i].valore;
        }
    return 300+max;
    }
    return 0;
}
int full(Carta mano[])
{
    int i,j,max=0;
    if(tris(mano)){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore!=tris(mano) && mano[i].valore>max)
                    max=mano[i].valore;
            }
        }
    }
    if(max==0)
        return 0;
    else return 100*tris(mano) + max;
}

int poker(Carta mano[])
{
    int i,j,h,k;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(h=0;h<7;h++){
                for(k=0;k<7;k++){
                    if(mano[i].valore==mano[j].valore && mano[j].valore==mano[h].valore && mano[h].valore==mano[k].valore
                       && i!=j && i!=h && i!=k && j!=h && j!=k && k!=h){
                        return mano[i].valore;
                    }
                }
            }
        }
    }
    return 0;
}

//Inizio scala colore
int trovaCartaColore(Carta mano[], int val, char seed)
{
    int i;
    for(i=0;i<7;i++){
        if(mano[i].valore==14 && mano[i].seme==seed && val==1)
            return 1;
        if(mano[i].valore==val && mano[i].seme==seed && val!=1)
            return 1;
    }
    return 0;
}

int scalaColore(Carta mano[]) //vd. Funzione scala
{
    int i=0,status=0;
    sort(mano);
    while(i<7 && status<4){
        if(trovaCartaColore(mano,mano[i].valore - status, mano[i].seme)==1)
            status++;
        else{
            i++;
            status=0;
        }
    }
    if(status==4)
        return mano[i].valore;
    else
        return 0;
}
//Fine scala colore
