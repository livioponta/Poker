#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "test.h"
#include "prematch.h"
#include "match.h"

//FUNZIONI DI STAMPA

void printTurno(Partita p) //Stampa a schermo un turno
{                           //Da rivedere (es. aggiungere soldi giocatori)
    int i;
    printf("Tavolo:\n");
    for(i=0;i<5;i++){
        printCarta(p->t[i]);
        printf("-");
    }
    printf("\b\n\n");
    printf("Mani dei Giocatori:\n");
    while(p->g!=NULL){
        printCarta(p->g->c1);
        printf("-");
        printCarta(p->g->c2);
        printf("  ");
        p->g=p->g->next;
    }
    printf("\n\n");
}

void printCarta(Carta c) //Stampa una carta
{                       //Da migliorare per feedback visivo
    printf("%c%c",c.nome,c.seme);
}

