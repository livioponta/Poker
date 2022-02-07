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

Punteggio puntiMano(Giocatori g,Carta tavolo[5]) //Restituisce la struct Punteggio corrispondente alla mano + carte in tavola di un giocatore
{                                               //Da rivedere (interazione giocatori) (riconoscere giocatori in fold)
    int i;
    Punteggio punti;
    Carta tot[7];
    for(i=0;i<5;i++)
        tot[i]=tavolo[i];
    tot[5]=g->c1;
    tot[6]=g->c2;
    if(cartaAlta(tot)){
        punti.combinazione=0;
        punti.valore=cartaAlta(tot);
    }
    if(coppia(tot)){
        punti.combinazione=1;
        punti.valore=coppia(tot);
    }
    if(doppiaCoppia(tot)){
        punti.combinazione=2;
        punti.valore=doppiaCoppia(tot);
    }
    if(tris(tot)){
        punti.combinazione=3;
        punti.valore=tris(tot);
    }
    if(scala(tot)){
        punti.combinazione=4;
        punti.valore=scala(tot);
    }
    if(colore(tot)){
        punti.combinazione=5;
        punti.valore=colore(tot);
    }
    if(full(tot)){
        punti.combinazione=6;
        punti.valore=full(tot);
    }
    if(poker(tot)){
        punti.combinazione=7;
        punti.valore=poker(tot);
    }
    if(scalaColore(tot)){
        punti.combinazione=8;
        punti.valore=scalaColore(tot);
    }
}

int vincitoreTurno(Partita p) //Dato un turno, restituisce il numero del giocatore vincente
{                               //Da rivedere
    int i;
    Punteggio * punteggi;
    Punteggio maxPunteggio;
    int num,win;
    maxPunteggio.combinazione=0;
    maxPunteggio.valore=0;
    num=numGiocatori(p);
    punteggi=(Punteggio*)malloc(sizeof(Punteggio)*num);
    for(i=0;i<num;i++){
        punteggi[i]=puntiMano(p->g,p->t);
        p->g=p->g->next;
    }
    for(i=0;i<num;i++){
        if(punteggi[i].combinazione > maxPunteggio.combinazione){
            maxPunteggio.combinazione=punteggi[i].combinazione;
            maxPunteggio.valore=punteggi[i].valore;
            win=i;
        }
        if(punteggi[i].combinazione==maxPunteggio.combinazione && punteggi[i].valore>maxPunteggio.valore){
            maxPunteggio.valore=punteggi[i].valore;
            win=i;
        }
    }
    return win;
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
