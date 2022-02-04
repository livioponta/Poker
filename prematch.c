#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "test.h"
#include "match.h"

Giocatori insGiocatore(Giocatori g,int num)
{
    Giocatori q;
    q->numGiocatore=num;
    q->soldi=TOT;
    q->punti.combinazione=0;
    q->punti.valore=0;
    q->next=g;
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

Partita creaPartita(Partita p)
{
    Partita q;
    Giocatori g=NULL;
    q=(Partita)malloc(sizeof(Turno));
    q->piatto=0;
    g=creaGiocatori(g);
    q->g=g;
    q->next=p;
    return q;
}
