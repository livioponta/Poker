#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "prematch.h"
#include "match.h"

Partita insTurno(Partita p) //Inserisce manualmente un turno
{                           //Da rivedere
    Partita q;
    int f=1,count=1;
    printf("\nInserimento del Turno:\n\n");
    q=(Partita)malloc(sizeof(Turno));
    q->g=NULL;
    while(f==1){
        q->g=insGiocatore(q->g,count);
        count++;
        printf("\nPremere 1 per inserire altri giocatori;\nPremere 0 per uscire.\n\n");
        scanf("%d",&f);
    }
    insTavolo(q->t);
    q->next=p;
    return q;
}

void insTavolo(Carta c[]) //Inserisce manualmente le carte sul tavolo (Utile per test)
{                       //Da rivedere
    int i;
    for(i=0;i<5;i++){
        if(i==0)
            printf("Flop:\n");
        if(i==3)
            printf("Turn:\n");
        if(i==4)
            printf("River:\n");
        c[i]=scanCarta();
    }
}

Carta scanCarta() //Scannerizza una carta manualmente (Utile per test)
{
    Carta c;
    do{
        printf("Inserisci il valore della carta: ");
        scanf("%d",&c.valore);
        fflush(stdin);
    }while(c.valore<2 || c.valore>14);

    do{
        printf("Inserisci il seme della carta: ");
        fflush(stdin);
        scanf("%c",&c.seme);
        fflush(stdin);
    }while(c.seme!='c' && c.seme!='q' && c.seme!='f' && c.seme!='p');

    //Conversione valore carta
    if(c.valore>=2 && c.valore<=10)
        c.nome='0'+c.valore;
    if(c.valore==14)
        c.nome='A';
    if(c.valore==11)
        c.nome='J';
    if(c.valore==12)
        c.nome='Q';
    if(c.valore==13)
        c.nome='K';

    //Conversione seme carta
    if(c.seme=='c')
        c.seme=3;
    if(c.seme=='q')
        c.seme=4;
    if(c.seme=='f')
        c.seme=5;
    if(c.seme=='p')
        c.seme=6;
    return c;
}

void testPunteggio(Carta mano[])
{
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
    printf("\nPunti comb: %d\nPunti carte: %d\n", punti.combinazione, punti.valore);
}

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


