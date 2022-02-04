#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "test.h"
#include "match.h"



Partita creaPartita(Partita p)
{
    int i;
    Partita q;
    Giocatori g=NULL;
    q=(Partita)malloc(sizeof(Turno));
    q->piatto=0;
    g=creaGiocatori(g);
    q->g=g;
    for(i=0;i<5;i++){
        q->t[i].nome='-';
        q->t[i].seme='-';
        q->t[i].valore=0;
    }
    q->next=p;
    return q;
}
Giocatori creaGiocatori(Giocatori g)
{
    int i,quantiGiocatori;
    printf("Quanti giocatori?\n");
    scanf("%d",&quantiGiocatori);
    for(i=quantiGiocatori;i>0;i--){
        g=insGiocatore(g,i);
    }
    return g;
}
Giocatori insGiocatore(Giocatori g,int num)
{
    Giocatori q;
    q=(Giocatori)malloc(sizeof(Giocatore));
    q->numGiocatore=num;
    q->soldi=TOT;
    q->puntata=0;
    q->punti.combinazione=0;
    q->punti.valore=0;
    q->c1.nome='-';
    q->c1.seme='-';
    q->c1.valore=0;
    q->c2.nome='-';
    q->c2.seme='-';
    q->c2.valore=0;
    q->fold=0;
    q->next=g;
    return q;
}
