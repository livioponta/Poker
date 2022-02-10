#include<stdlib.h>
#include<stdio.h>

#define TOT 2000

#include "types.h"
#include "output.h"
#include "test.h"
#include "prematch.h"
#include "match.h"


int cartaAlta(Carta mano[])
{
    sort(mano); //Ritorna le prime 5 carte
    return 10000*mano[0].valore + 1000*mano[1].valore + 100*mano[2].valore + 10*mano[3].valore + mano[4].valore;
}

int coppia(Carta mano[])
{
    int max=0,i,j,swap;
    int c1=0,c2=0,c3=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore>max){
                max=mano[i].valore;
            }
        }
    }
    for(i=0;i<7;i++){
        if(mano[i].valore!=max && mano[i].valore!=c1 && mano[i].valore!=c2 && mano[i].valore > c3){
            c3=mano[i].valore;
            if(c3>c2){
                swap=c3;
                c3=c2;   //Trova il valore delle tre carte maggiori
                c2=swap;
            }
            if(c2>c1){
                swap=c2;
                c2=c1;
                c1=swap;
            }

        }
    }
    if(max==0)
        return 0;
    
    return 1000*max + 100*c1 + 10*c2 + c3;
}

int doppiaCoppia(Carta mano[])
{
    int c1=0,c2=0,c3=0,i,j,swap;
    if(coppia(mano)){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore>c2 && mano[i].valore!=c1){
                    c2=mano[i].valore; //Inserisce una coppia in c2 se ha il valore maggiore del suo e diverso da c1
                    if(c2>c1){
                        swap=c2;
                        c2=c1;
                        c1=swap;  //Scambia c2 con c1 se è maggiore di quest'ultimo
                    }
                }
            }
        }

        for(i=0;i<7;i++){ //Carta extra
            if(mano[i].valore!=c1 && mano[i].valore!=c2 && mano[i].valore > c3)
                c3=mano[i].valore;
        }
    }

    if(c1==0 || c2==0)
        return 0;
    else
        return c1*100 + c2*10 + c3; //La coppia più alta è determinante
}

int tris(Carta mano[])
{
    int max=0,i,j,k,swap;
    int c1=0,c2=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(k=0;k<7;k++){
                if(mano[i].valore==mano[j].valore && mano[j].valore==mano[k].valore && i!=j && j!=k && k!=i && mano[i].valore>max)
                    max=mano[i].valore;
            }
        }
    }
    for(i=0;i<7;i++){ //Trova il valore delle due carte maggiori diverse dal tris
        if(mano[i].valore!=max && mano[i].valore!=c1 && mano[i].valore>c2){
            c2=mano[i].valore;
            if(c2>c1){
                swap=c2;
                c2=c1;
                c1=swap;
            }

        }
    }

    if(max==0)
        return 0;

    return 100*max + 10*c1 + c2;
}

int scala(Carta mano[])
{
    int i=0,status=0; //i posizione nell'array
    sort(mano);       //Per selezionare la scala maggiore si fa riferimento a carte ordinate dal valore maggiore al minore
    while(i<7 && status<5){
        if(trovaCarta(mano, mano[i].valore - status) == 1)
            status++;
        else{
            status=0;
            i++;
        }
    }
    if(status==5) //Quando status (completamento scala) arriva a 4 si ritorna il valore della scala (carta più alta)
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
    int i,j,k;
    int c=0,t=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(k=0;k<7;k++){
                if(mano[i].valore==mano[j].valore && mano[j].valore==mano[k].valore && i!=j && j!=k && k!=i && mano[i].valore>t)
                    t=mano[i].valore; //Trova il valore del tris
            }
        }
    }
    if(t!=0){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                if(mano[i].valore==mano[j].valore && i!=j && mano[i].valore!=t && mano[i].valore>c)
                    c=mano[i].valore; //Trova il valore della coppia
            }
        }
    }
    if(c==0 || t==0)
        return 0;
    
    return 10*t + c;
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

int scalaColore(Carta mano[]) //vd. Funzione scala
{
    int i=0,status=0;
    sort(mano);
    while(i<7 && status<5){
        if(trovaCartaColore(mano,mano[i].valore - status, mano[i].seme)==1)
            status++;
        else{
            i++;
            status=0;
        }
    }
    if(status==5)
        return mano[i].valore;
    else
        return 0;
}

