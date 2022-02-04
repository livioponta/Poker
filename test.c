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
{
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
    if(c.valore==1)
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
        c.seme=6
    return c;
}
