#include<stdio.h>
#include<stdlib.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "test.h"
#include "prematch.h"
#include "match.h"

//FUNZIONI DI STAMPA

void printPartita(Partita p)
{
    printf("-----------------------------------\n\n");
    printGiocatori(p->g);
    printf("\nPiatto: %d\n\n",p->piatto);
    printTavolo(p->t);
    printf("\n");
}
void printGiocatori(Giocatori g)
{
    while(g!=NULL){
        printf("Giocatore %d: (%c%c,%c%c) Soldi:%d  Puntata: %d\n\n",g->numGiocatore,g->c1.nome,g->c1.seme,g->c2.nome,g->c2.seme,g->soldi,g->puntata);
        g=g->next;
    }
}
void printTavolo(Carta tavolo[])
{
    int i;
    printf("Tavolo:  ");
    for(i=0;i<5;i++){
        printCarta(tavolo[i]);
        printf(" ");
    }
}
void printCarta(Carta c)
{
    printf("%c%c",c.nome,c.seme);
}

