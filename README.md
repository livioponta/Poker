# Poker

Strutture dati
---------------
vd. *types.h* per info <br />
Viene definita una lista di turni, contenente i soldi presenti sul piatto e 5 slot per le carte sul tavolo <br />
A ogni turno, viene associata una lista di giocatori, ognuno dei quali possiede campi per memorizzare, a ogni turno, <br />
i soldi puntati, le carte in mano e il punteggio che deriva dalla sua combinazione a fine turno.

Partita
---------
* Bisogna creare il turno (Nodo della lista partita) per procedere ogni turno
* Ogni turno, va ricreato il mazzo, creato da una funzione come un vettore ordinato di carte
* Il mazzo viene mischiato da una funzione apposita
* Le carte vengono distribuite a ogni giocatore
* 

Combinazioni
--------------

Combinazioni ordinate con delle struct Punteggio, in cui figura il punteggio della combinazione (Gerarchia combinazioni poker) (0-8) <br />
e quello delle carte (Per stabilire chi vince a parità di combinazione) (Variabile). <br />
N.B. I punteggi non sono visibili in gioco <br />
N.B. L'asso per comodità vale 14 e viene valutato 1 solo dalle funzioni della scala e della scala colore <br />


**COMBINAZIONI CON MENO DI 5 CARTE**

**Carta alta** <br />
Punti combinazione: 0 <br />
Punti carte:
* (65432-154320) corrispondono a 10000*(Valore Carta alta) + 1000*(2a Carta alta) + 100*(3a Carta alta) + 10*(4a Carta alta) + (5a Carta alta)
* Oltre alla carta alta, le 4 carte maggiori della mano possono spareggiare due combinazioni

**Coppia** <br />
Punti combinazione: 1 <br />
Punti carte:
* (2543-15431) corrispondono a 1000*(Valore Coppia) + 100*(Valore Carta alta) + 10*(2a Carta alta) + (3a Carta alta)
* Oltre alla coppia, le 3 carte maggiori della mano possono spareggiare due combinazioni

**Doppia Coppia** <br />
Punti combinazione: 2 <br />
* (324-1542) corrispondono a 100*(Valore 1a coppia) + 10*(Valore 2a coppia) + (Valore Carta alta)
* Oltre alla doppia coppia, la carta maggiore della mano può spareggiare due combinazioni

**Tris** <br />
Punti combinazione: 3
* (243-1542) corrispondono a 100*(Valore tris) + 10*(Valore Carta alta) + (2a Carta alta)
* Oltre al tris, le 2 carte maggiori della mano possono spareggiare due combinazioni

**COMBINAZIONI CON 5 CARTE**

**Scala** <br />
Punti combinazione: 4 <br />
Punti carte: <br />
* (5-14) corrispondono al valore della carta più alta della scala <br />

**Colore** <br />
Punti combinazione: 5 <br />
Punti carte: <br />
* (6-314) corrispondono a (Fattore seme)*100 + (Valore carta più alta) <br />
* Fattore seme: 0 picche, 1 fiori, 2 quadri, 3 cuori <br />

**Full** <br />
Punti combinazione: 6 <br />
Punti carte: <br />
* (203-1413) corrispondono a (Valore carta tris)*10 + (Valore carta coppia) <br />

**Poker** <br />
Punti combinazione: 7 <br />
Punti carte: <br />
* (2-14) corrispondono al valore della carta del poker <br />

**Scala Colore** <br />
Punti combinazione: 8 <br />
Punti carte: <br />
* (5-14) corrispondono al valore della carta più alta della scala <br />
* Non si tiene conto del seme della scala colore in quanto è impossibile la presenza in contemporanea di scale reali con semi diversi <br />
