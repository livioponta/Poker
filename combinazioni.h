#ifndef COMBINAZIONI_H_INCLUDED
#define COMBINAZIONI_H_INCLUDED

#include "types.h"
#include "output.h"
#include "test.h"
#include "prematch.h"
#include "match.h"

int cartaAlta(Carta mano[]);
int coppia(Carta mano[]);
int doppiaCoppia(Carta mano[]);
int tris(Carta mano[]);
int scala(Carta mano[]);
int colore(Carta mano[]);
int full(Carta mano[]);
int poker(Carta mano[]);
int scalaColore(Carta mano[]);

#endif // COMBINAZIONI_H_INCLUDED
