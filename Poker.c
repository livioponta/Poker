#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int valore;
    char nome;
    char seme;
}Carta;


typedef struct EM{
    Carta c1,c2;
    int numGiocatore;
    struct EM * next;
}Giocatore;
typedef Giocatore * Giocatori;

typedef struct EP{
    Giocatori g;
    Carta t[5];
    struct EP * next;
}Turno;
typedef Turno * Partita;

typedef struct{
    int combinazione;
    int valore;
}Punteggio;



Partita insTurno(Partita p);
    Giocatori insGiocatore(Giocatori g,int num);
    void insTavolo(Carta c[]);
        Carta scanCarta();

void printTurno(Partita p);
    void printCarta(Carta c);

int vincitoreTurno(Partita p);
    Punteggio puntiMano(Giocatori g,Carta tavolo[5]);
        int cartaAlta(Carta mano[]);
        int coppia(Carta mano[]);
        int doppiaCoppia(Carta mano[]);
        int tris(Carta mano[]);
        int scala(Carta mano[]);
        int colore(Carta mano[]);
        int full(Carta mano[]);
        int poker(Carta mano[]);
        int scalaColore(Carta mano[]);

int numGiocatori(Partita p);
void creaMazzo(Carta mazzo[]);
void pescaCarte(Carta mazzo[],Carta mano[],int quanteCarte);

int main()
{
    
    return 0;
}

int vincitoreTurno(Partita p)
{
    int i;
    Punteggio * punteggi;
    Punteggio maxPunteggio;
    int num,win;
    maxPunteggio.combinazione=0;
    maxPunteggio.valore=0;
    num=numGiocatori(p);
    punteggi=(Punteggio*)malloc(sizeof(Punteggio)*num);
    for(i=0;i<num;i++){
        punteggi[i]=puntiMano(p->g,p->t);
        p->g=p->g->next;
    }
    for(i=0;i<num;i++){
        if(punteggi[i].combinazione > maxPunteggio.combinazione){
            maxPunteggio.combinazione=punteggi[i].combinazione;
            maxPunteggio.valore=punteggi[i].valore;
            win=i;
        }
        if(punteggi[i].combinazione==maxPunteggio.combinazione && punteggi[i].valore>maxPunteggio.valore){
            maxPunteggio.valore=punteggi[i].valore;
            win=i;
        }
    }
    return win;
}
Punteggio puntiMano(Giocatori g,Carta tavolo[5])
{
    int i;
    Punteggio punti;
    Carta tot[7];
    for(i=0;i<5;i++)
        tot[i]=tavolo[i];
    tot[5]=g->c1;
    tot[6]=g->c2;
    if(cartaAlta(tot)){
        punti.combinazione=0;
        punti.valore=cartaAlta(tot);
    }
    if(coppia(tot)){
        punti.combinazione=1;
        punti.valore=coppia(tot);
    }
    if(doppiaCoppia(tot)){
        punti.combinazione=2;
        punti.valore=doppiaCoppia(tot);
    }
    if(tris(tot)){
        punti.combinazione=3;
        punti.valore=tris(tot);
    }
    if(scala(tot)){
        punti.combinazione=4;
        punti.valore=scala(tot);
    }
    if(colore(tot)){
        punti.combinazione=5;
        punti.valore=colore(tot);
    }
    if(full(tot)){
        punti.combinazione=6;
        punti.valore=full(tot);
    }
    if(poker(tot)){
        punti.combinazione=7;
        punti.valore=poker(tot);
    }
    if(scalaColore(tot)){
        punti.combinazione=8;
        punti.valore=scalaColore(tot);
    }
}
int cartaAlta(Carta mano[])
{
    int max,i;
    for(i=0;i<7;i++){
        if(mano[i].valore==1)
            return 14;
        if(mano[i].valore>max)
            max=mano[i].valore;
    }
    return max;
}
int coppia(Carta mano[])
{
    int i,j;
    int max=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(mano[i].valore==mano[j].valore && i!=j && (mano[i].valore>max || mano[i].valore==1)){
                if(mano[i].valore==1)
                    return 14;
                max=mano[i].valore;
            }
        }
    }
    return max;
}
int doppiaCoppia(Carta mano[])
{
    int c1=0,c2=0,i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(mano[i].valore==mano[j].valore && i!=j){
                if(c1==0){
                    if(mano[i].valore==1)
                        c1=14;
                    c1=mano[i].valore;
                }

                else if(c2==0){
                    if(mano[i].valore==1)
                        c2=14;
                    c2=mano[i].valore;
                }

                else if(c1!=0 && c1<=c2 && (mano[i].valore>c1 || mano[i].valore==1)){
                    if(mano[i].valore==1)
                        c1=14;
                    c1=mano[i].valore;
                }

                else if(c2!=0 && c2<c1 && (mano[i].valore>c1 || mano[i].valore==1)){
                    if(mano[i].valore==1)
                        c2=14;
                    c2=mano[i].valore;
                }



            }
        }
    }
    if(c1==0 || c2==0)
        return 0;
    if(c1>c2)
        return c2*100+c1;
    else
        return c1*100+c2;
}
int tris(Carta mano[])
{
    int i,j,k,max=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(k=0;k<7;k++){
                if(mano[i].valore==mano[j].valore && mano[j].valore==mano[k].valore && i!=j && i!=k && j!=k){
                    if(mano[i].valore==1)
                        return 14;
                    max=mano[i].valore;
                }
            }
        }
    }
    return max;
}
int scala(Carta mano[])
{

}
int colore(Carta mano[])
{
    int i,cp=0,cf=0,cc=0,cq=0,max=0;
    for(i=0;i<7;i++){
        if(mano[i].seme=='p')
            cp++;
        if(mano[i].seme=='f')
            cf++;
        if(mano[i].seme=='c')
            cc++;
        if(mano[i].seme=='q')
            cq++;
    }
    if(cp>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='p')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return max;
    if(cf>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='f')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 100+max;
    if(cq>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='q')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 200+max;
    if(cc>4)
        for(i=0;i<7;i++){
            if(mano[i].valore>max && mano[i].seme=='c')
                max=mano[i].valore;
            if(mano[i].valore==1)
                max=14;
        }
    return 300+max;
    return 0;
}
int full(Carta mano[]);
int poker(Carta mano[])
{
    int i,j,h,k;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            for(h=0;h<7;h++){
                for(k=0;k<7;k++){
                    if(mano[i].valore==mano[j].valore && mano[j].valore==mano[h].valore && mano[h].valore==mano[k].valore && i!=j && i!=h && i!=k
                       && j!=h && j!=k && k!=h){
                        if(mano[i].valore==1)
                            return 14;
                        return mano[i].valore;
                    }
                }
            }
        }
    }
    return 0;
}
int scalaColore(Carta mano[]);

void creaMazzo(Carta mazzo[])
{
    int i,j,count=0;
    for(i=1;i<14;i++){
        for(j=1;j<5;j++){
            mazzo[count].valore=i;
            if(j==1)
                mazzo[count].seme='c';
            if(j==2)
                mazzo[count].seme='q';
            if(j==3)
                mazzo[count].seme='f';
            if(j==4)
                mazzo[count].seme='p';
            if(mazzo[count].valore>=2 && mazzo[count].valore<=9)
                mazzo[count].nome='0'+mazzo[count].valore;
            if(mazzo[count].valore==1)
                mazzo[count].nome='A';
            if(mazzo[count].valore==10)
                mazzo[count].nome='T';
            if(mazzo[count].valore==11)
                mazzo[count].nome='J';
            if(mazzo[count].valore==12)
                mazzo[count].nome='Q';
            if(mazzo[count].valore==13)
                mazzo[count].nome='K';
            count++;
        }
    }
}
void pescaCarte(Carta mazzo[],Carta mano[],int quanteCarte)
{
    int r,i,j,f;
    srand(time(0));
    do{
        f=1;
        for(i=0;i<quanteCarte;i++){
            r=rand()%52;
            mano[i]=mazzo[r];
        }
        for(i=0;i<quanteCarte;i++){
            for(j=0;j<quanteCarte;j++){
                if(mano[i].valore==mano[j].valore && mano[i].seme==mano[i].seme && i!=j)
                    f=0;
            }
        }
    }while(f==0);
}
int numGiocatori(Partita p)
{
    int count;
    while(p->g!=NULL){
        count++;
        p->g=p->g->next;
    }
    return count;
}


Partita insTurno(Partita p)
{
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
Giocatori insGiocatore(Giocatori g,int num)
{
    Giocatori q;
    q=(Giocatori)malloc(sizeof(Giocatore));
    printf("Inserisci la prima carta\n");
    q->c1=scanCarta();
    printf("Inserisci la seconda carta\n");
    q->c2=scanCarta();
    q->numGiocatore=num;
    q->next=NULL;
    if(g==NULL)
        return q;
    Giocatori temp=g;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=q;
    return g;
}
void insTavolo(Carta c[])
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
Carta scanCarta()
{
    Carta c;
    do{
        printf("Inserisci il valore della carta: ");
        scanf("%d",&c.valore);
        fflush(stdin);
    }while(c.valore<1 || c.valore>13);

    do{
        printf("Inserisci il seme della carta: ");
        fflush(stdin);
        scanf("%c",&c.seme);
        fflush(stdin);
    }while(c.seme!='c' && c.seme!='q' && c.seme!='f' && c.seme!='p');

    printf("Inserisci il seme della carta: ");
    scanf("%c",&c.seme);
    fflush(stdin);
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
    return c;
}
void printTurno(Partita p)
{
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
void printCarta(Carta c)
{
    printf("%c%c",c.nome,c.seme);
}
