#ifndef MATCH_H_INCLUDED
#define MATCH_H_INCLUDED

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "test.h"
#include "prematch.h"

int numGiocatori(Partita p);

void creaMazzo(Carta mazzo[]);
void mischia(Carta mazzo[], size_t n);
void pescaCarte(Carta mazzo[],Carta mano[],int quanteCarte);

Punteggio puntiMano(Giocatori g,Carta tavolo[5]);
int vincitoreTurno(Partita p);

void distribuisciCarte(Partita p,Carta mazzo[]);
void distribuisciFlop(Partita p,Carta mazzo[]);
void distribuisciTurn(Partita p,Carta mazzo[]);
void distribuisciRiver(Partita p,Carta mazzo[]);

#endif // MATCH_H_INCLUDED
