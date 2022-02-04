#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOT 2000

#include "types.h"
#include "combinazioni.h"
#include "output.h"
#include "test.h"
#include "match.h"
#include "prematch.h"


int main()
{
    int menu=1;
    int num;
    Giocatori g;
    Partita p=NULL;
    Carta mazzo[52];
    Carta mano[2];
    creaMazzo(mazzo);


    for(int i=0;i<2;i++){
        mano[i]=mazzo[i];
        printCarta(mazzo[i]);
        printf("\n");
    }

    printf("\ncoppia: %d",coppia(mano));

    return 0;
}



