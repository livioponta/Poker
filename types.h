#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef struct{ //DEFINIZIONE CARTA
    int valore;
    char nome;
    char seme;
}Carta;

typedef struct{ //DEFINIZIONE PUNTEGGIO (= Definito per creare gerarchia tra combinazini)
    int combinazione; //Dipende 1) Dalla combinazione (0-8) 2) Dalle carte coinvolte
    int valore;
}Punteggio;

typedef struct EM{ //DEFINIZIONE LISTA GIOCATORI
    Carta c1,c2;
    int numGiocatore;
    int soldi; //Definiti all'inizio della partita
    int puntata;
    int fold;
    Punteggio punti; //0 fino a river, Poi punteggio definito da combinazioni, 0 per i giocatori in fold
    struct EM * next;
}Giocatore;
typedef Giocatore * Giocatori;

typedef struct EP{ //DEFINIZIONE LISTA TURNO (Turno include giocatori + carte sul tavolo)
    Giocatori g;
    Carta t[5];
    int piatto;
    struct EP * next;
}Turno;
typedef Turno * Partita;


#endif // TYPES_H_INCLUDED
