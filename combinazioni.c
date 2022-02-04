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
    int max,i;
    for(i=0;i<7;i++){
        if(mano[i].valore==1)
            return 14;
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
            if(mano[i].valore==mano[j].valore && i!=j && (mano[i].valore>max || mano[i].valore==1)){
                if(mano[i].valore==1)
                    return 14;
                max=mano[i].valore;
            }
        }
    }
    return max;
}
int doppiaCoppia(Carta mano[])
{
    int c1=0,c2=0,i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(mano[i].valore==mano[j].valore && i!=j){
                if(c1==0){
                    if(mano[i].valore==1)
                        c1=14;
                    c1=mano[i].valore;
                }

                else if(c2==0){
                    if(mano[i].valore==1)
                        c2=14;
                    c2=mano[i].valore;
                }

                else if(c1!=0 && c1<=c2 && (mano[i].valore>c1 || mano[i].valore==1)){
                    if(mano[i].valore==1)
                        c1=14;
                    c1=mano[i].valore;
                }

                else if(c2!=0 && c2<c1 && (mano[i].valore>c1 || mano[i].valore==1)){
                    if(mano[i].valore==1)
                        c2=14;
                    c2=mano[i].valore;
                }



            }
        }
    }
    if(c1==0 || c2==0)
        return 0;
    if(c1>c2)
        return c2*100+c1;
    else
        return c1*100+c2;
}
int tris(Carta mano[])
{
    int i,j,k,max=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(k=0;k<7;k++){
                if(mano[i].valore==mano[j].valore && mano[j].valore==mano[k].valore && i!=j && i!=k && j!=k){
                    if(mano[i].valore==1)
                        return 14;
                    max=mano[i].valore;
                }
            }
        }
    }
    return max;
}

int trovaCarta(Carta mano[], int val) //Da segnare in prototipi
{
    int i;
    for(i=0;i<7;i++){
        if(mano[i].valore==val)
            return 1;
    }
    return 0;
}

int scala(Carta mano[]) //Da segnare in prototipi
{
int i=0,status=0;
while(status<4 && i<7){
    if(trovaCarta(mano,mano[i].valore + status)==1)
        status++;
    else{
        i++;
        status=0;
    }
}
if(status==4)
    return mano[i].valore + status;
else
    return 0;
}

int colore(Carta mano[])
{
    int i,cp=0,cf=0,cc=0,cq=0,max=0;
    for(i=0;i<7;i++){
        if(mano[i].seme=='p')
            cp++;
        if(mano[i].seme=='f')
            cf++;
        if(mano[i].seme=='c')
            cc++;
        if(mano[i].seme=='q')
            cq++;
    }
    if(cp>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='p')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return max;
    if(cf>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='f')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 100+max;
    if(cq>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='q')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 200+max;
    if(cc>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='c')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 300+max;
    return 0;
}
int full(Carta mano[]);
int poker(Carta mano[])
{
    int i,j,h,k;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(h=0;h<7;h++){
                for(k=0;k<7;k++){
                    if(mano[i].valore==mano[j].valore && mano[j].valore==mano[h].valore && mano[h].valore==mano[k].valore && i!=j && i!=h && i!=k
                       && j!=h && j!=k && k!=h){
                        if(mano[i].valore==1)
                            return 14;
                        return mano[i].valore;
                    }
                }
            }
        }
    }
    return 0;
}
int scalaColore(Carta mano[]);
