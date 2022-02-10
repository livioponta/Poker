#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "test.h"
#include "prematch.h"

int numGiocatori(Partita p) //Restituisce numero giocatori data una partita
{
    int count;
    Giocatori temp=p->g;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count;
}

void creaMazzo(Carta mazzo[]) //Crea una lista mazzo ordinata
{
    int i,j,count=0;
    for(i=2;i<15;i++){
        for(j=1;j<5;j++){
            mazzo[count].valore=i;
            if(j==1)
                mazzo[count].seme=3;
            if(j==2)
                mazzo[count].seme=4;
            if(j==3)
                mazzo[count].seme=5;
            if(j==4)
                mazzo[count].seme=6;
            if(mazzo[count].valore>=2 && mazzo[count].valore<=9)
                mazzo[count].nome='0'+mazzo[count].valore;
            if(mazzo[count].valore==14)
                mazzo[count].nome='A';
            if(mazzo[count].valore==10)
                mazzo[count].nome='T';
            if(mazzo[count].valore==11)
                mazzo[count].nome='J';
            if(mazzo[count].valore==12)
                mazzo[count].nome='Q';
            if(mazzo[count].valore==13)
                mazzo[count].nome='K';
            count++;
        }
    }
}

void mischia(Carta mazzo[], size_t n) //Mischia la lista mazzo iniziale ordinata
{                                     //Poi sarà sempre disordinata
    if (n > 1) {
        size_t i,j;
        Carta t;
        for (i = 0; i < n - 1; i++){
          j = i + rand() / (RAND_MAX / (n - i) + 1);
          t = mazzo[j];
          mazzo[j] = mazzo[i];
          mazzo[i] = t;
        }
    }
}

void pescaCarte(Carta mazzo[],Carta mano[],int n) //Pesca le prime n carte del mazzo e sposta le altre in avanti
{                                                 //Da modificare per tenere shuffle e pescare e sostituire le prime carte
    int r,i,j,f;
    srand(time(0));
    do{
        f=1;
        for(i=0;i<n;i++){
            r=rand()%52;
            mano[i]=mazzo[r];
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(mano[i].valore==mano[j].valore && mano[i].seme==mano[i].seme && i!=j)
                    f=0;
            }
        }
    }while(f==0);
}

Punteggio puntiMano(Carta mano[]) //Restituisce la struct Punteggio corrispondente a una mano di 7 carte
{
    int i;
    Punteggio punti;
    if(cartaAlta(mano)){
        punti.combinazione=0;
        punti.valore=cartaAlta(mano);
    }
    if(coppia(mano)){
        punti.combinazione=1;
        punti.valore=coppia(mano);
    }
    if(doppiaCoppia(mano)){
        punti.combinazione=2;
        punti.valore=doppiaCoppia(mano);
    }
    if(tris(mano)){
        punti.combinazione=3;
        punti.valore=tris(mano);
    }
    if(scala(mano)){
        punti.combinazione=4;
        punti.valore=scala(mano);
    }
    if(colore(mano)){
        punti.combinazione=5;
        punti.valore=colore(mano);
    }
    if(full(mano)){
        punti.combinazione=6;
        punti.valore=full(mano);
    }
    if(poker(mano)){
        punti.combinazione=7;
        punti.valore=poker(mano);
    }
    if(scalaColore(mano)){
        punti.combinazione=8;
        punti.valore=scalaColore(mano);
    }

    return punti;
}

Giocatori aggiornaPunteggio(Giocatori g, Carta tavolo[])
{
    Giocatori cur;
    Carta tot[7];
    Punteggio temp;
    int i;
    cur=g;

    while(cur!=NULL){
        if(g->punti.combinazione == -1){
            cur->punti.combinazione=0;
            cur->punti.valore=0;
        }
        else{
            for(i=0;i<5;i++)
                tot[i]=tavolo[i];
            tot[5]=cur->c1;
            tot[6]=cur->c2;
            temp=puntiMano(tot);
            cur->punti.combinazione=temp.combinazione;
            cur->punti.valore=temp.valore;
        }
        cur=cur->next;
    }

    return g;
}

Punteggio maxPunteggio(Partita p) //Dato un turno, restituisce il punteggio vincente
{
    Punteggio max;
    max.combinazione=0;
    max.valore=0;
    Giocatori cur=p->g;
    while(cur!=NULL){
        if(cur->punti.combinazione > max.combinazione){
            max.combinazione=cur->punti.combinazione;
            max.valore=cur->punti.valore;
        }
        if(cur->punti.combinazione == max.combinazione && cur->punti.valore > max.valore)
            max.valore=cur->punti.valore;
    }
    return max;
}

void distribuisciCarte(Partita p,Carta mazzo[52])
{
    int c=0;
    Giocatori temp=p->g;
    while(temp!=NULL){
        temp->c1=mazzo[c];
        c++;
        temp->c2=mazzo[c];
        c++;
        temp=temp->next;
    }
}
void distribuisciFlop(Partita p,Carta mazzo[])
{
    int num=numGiocatori(p),i;
    for(i=0;i<3;i++){
        p->t[i]=mazzo[num*2+i];
    }
}
void distribuisciTurn(Partita p,Carta mazzo[])
{
    int num=numGiocatori(p);
    p->t[3]=mazzo[num*2+3];
}
void distribuisciRiver(Partita p,Carta mazzo[])
{
    int num=numGiocatori(p);
    p->t[4]=mazzo[num*2+4];
}

void giroPuntate(Partita p,int posIn,int sBlind)
{
    Giocatori temp=p->g;
    int i;
    for(i=0;i<posIn;i++){
        temp=temp->next;
    }
    if(p->t[0].nome=='-'){
        primaPunta(p->g,temp,sBlind);
    }
    else{
        Punta(p->g,temp,sBlind,numGiocatori(p));
    }
    temp=p->g;
    while(temp!=NULL){
        p->piatto=p->piatto+temp->puntata;
        temp->puntata=0;
        temp=temp->next;
    }
}
void Punta(Giocatori g,Giocatori temp,int sBlind,int numGioc)
{
    int maxPuntata=0,maxPuntataPrec=0,i=0,menu;
    while(temp->puntata!=maxPuntata || i<numGioc){
        if(temp->punti.combinazione!=-1){
            do{
            printf("Giocatore %d:\nPer chiamare %d premi 1;\nPer rialzare premi 2;\nPer foldare premi 0.\n\n",
                   temp->numGiocatore,maxPuntata-temp->puntata);
            scanf("%d",&menu);
            }while(menu!=1&&menu!=2&&menu!=0);
            switch(menu){
                case 1:
                    temp->soldi=temp->soldi-(maxPuntata-temp->puntata);
                    temp->puntata=maxPuntata;
                    break;
                case 2:
                    do{
                    printf("A quanto vuoi rialzare?");
                    scanf("%d",&maxPuntata);
                    }while(maxPuntata<2*maxPuntataPrec);
                    maxPuntataPrec=maxPuntata;
                    temp->soldi=temp->soldi-(maxPuntata-temp->puntata);
                    temp->puntata=maxPuntata;
                    break;
                case 0:
                    temp->punti.combinazione=-1;
            }
        }
        temp=temp->next;
        if(temp==NULL){
            temp=g;
        }
        i++;
    }
}
void primaPunta(Giocatori g,Giocatori temp,int sBlind)
{
    int maxPuntata,maxPuntataPrec,menu;
    temp->puntata=sBlind;
    temp->soldi=temp->soldi-temp->puntata;
    if(temp->next!=NULL){
        temp=temp->next;
        temp->puntata=2*sBlind;
        temp->soldi=temp->soldi-temp->puntata;
    }
    else{
        temp=g;
        temp->puntata=sBlind;
        temp->soldi=temp->soldi-temp->puntata;
    }
    if(temp->next!=NULL){
        temp=temp->next;
    }
    else{
        temp=g;
    }
    maxPuntata=2*sBlind;
    maxPuntataPrec=maxPuntata;
    while(temp->puntata!=maxPuntata){
        if(temp->punti.combinazione!=-1){
            do{
            printf("Giocatore %d:\nPer chiamare %d premi 1;\nPer rialzare premi 2;\nPer foldare premi 0.\n\n",
                   temp->numGiocatore,maxPuntata-temp->puntata);
            scanf("%d",&menu);
            }while(menu!=1&&menu!=2&&menu!=0);
            switch(menu){
                case 1:
                    temp->soldi=temp->soldi-(maxPuntata-temp->puntata);
                    temp->puntata=maxPuntata;
                    break;
                case 2:
                    do{
                    printf("A quanto vuoi rialzare?");
                    scanf("%d",&maxPuntata);
                    }while(maxPuntata<2*maxPuntataPrec);
                    maxPuntataPrec=maxPuntata;
                    temp->soldi=temp->soldi-(maxPuntata-temp->puntata);
                    temp->puntata=maxPuntata;
                    break;
                case 0:
                    temp->punti.combinazione=-1;
            }
        }
        temp=temp->next;
        if(temp==NULL){
            temp=g;
        }
    }
}
