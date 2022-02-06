# Poker

Partita
---------
Vince alla fine chi ha più punti, chi folda/non chiama ha punteggio = -1, chi ha il punteggio = -1 salta il turno
Buio --> funzione eseguita ogni inizio turno --> Input: lista giocatori, numero giocatori, puntata buio --> sottrae al giocatore del giro il buio a inizio turno
CheckSconfitta --> funzione eseguita a inizio turno --> Input: lista giocatori --> se un giocatore arriva a 0 fiches, rimuove dalla lista

Turno --> 3 Casi --> Fold, Check, Punta

Combinazioni
--------------

Combinazioni ordinate con delle struct Punteggio, in cui figura il punteggio della combinazione (Gerarchia combinazioni poker) (0-8)
e quello delle carte (Per stabilire chi vince a parità di combinazione) (Variabile).
N.B. I punteggi non sono visibili in gioco


**COMBINAZIONI CON MENO DI 5 CARTE**

**Carta alta** <br />
Punti combinazione: 0 <br />
Punti carte:
* (2-14) corrispondono al valore della carta alta

**Coppia** <br />
Punti combinazione: 1 <br />
Punti carte:
* to do
* 5 carte fuori dalla coppia da considerare

**Doppia Coppia** <br />
Punti combinazione: 2 <br />
* to do
* 3 carte fuori dalla doppia coppia

**Tris** <br />
Punti combinazione: 3
* to do
* 4 carte fuori dal tris

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
* (203-1413) corrispondono a (Valore carta tris)*100 + (Valore carta coppia) <br />

**Poker** <br />
Punti combinazione: 7 <br />
Punti carte: <br />
* (2-14) corrispondono al valore della carta del poker <br />

**Scala Colore** <br />
Punti combinazione: 8 <br />
Punti carte: <br />
* (5-14) corrispondono al valore della carta più alta della scala <br />
* Non si tiene conto del seme della scala colore in quanto è impossibile la presenza in contemporanea di scale reali con semi diversi <br />
