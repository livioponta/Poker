#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "prematch.h"
#include "match.h"

Partita insTurno(Partita p);
void insTavolo(Carta c[]);
Carta scanCarta();
void testPunteggio(Carta mano[]);

#endif // TEST_H_INCLUDED
