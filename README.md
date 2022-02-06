# Poker

//GIRO PARTITA
Vince alla fine chi ha più punti, chi folda/non chiama ha punteggio = -1, chi ha il punteggio = -1 salta il turno
Buio --> funzione eseguita ogni inizio turno --> Input: lista giocatori, numero giocatori, puntata buio --> sottrae al giocatore del giro il buio a inizio turno
CheckSconfitta --> funzione eseguita a inizio turno --> Input: lista giocatori --> se un giocatore arriva a 0 fiches, rimuove dalla lista

Turno --> 3 Casi --> Fold, Check, Punta



Combinazioni ordinate con delle struct Punteggio, in cui figura il punteggio della combinazione (Gerarchia combinazioni poker) (0-8)
e quello delle carte (Per stabilire chi vince a parità di combinazione) (Variabile).
N.B. I punteggi non sono visibili in gioco


**COMBINAZIONI CON MENO DI 5 CARTE**

**-Carta alta**
Punti combinazione: 0

**-Coppia**
Punti combinazione: 1

**-Doppia Coppia**
Punti combinazione: 2

**-Tris**
Punti combinazione: 3

**COMBINAZIONI CON 5 CARTE**

**-Scala**
Punti combinazione: 4 <br />
Punti carte: <br />
(5-14) corrispondono al valore della carta più alta della scala

-**Colore
Punti combinazione:** 5
**Punti carte:**
(6-314) corrispondono a (Fattore seme)*100 + (Valore carta più alta)
Fattore seme: 0 picche, 1 fiori, 2 quadri, 3 cuori

**-Full
Punti combinazione:** 6
Punti carte:
(203-1413) corrispondono a (Valore carta tris)*100 + (Valore carta coppia)

**-Poker
Punti combinazione:** 7
**Punti carte:**
(2-14) corrispondono al valore della carta del poker

**-Scala Colore
Punti combinazione:** 8
**Punti carte:**
(5-14) corrispondono al valore della carta più alta della scala
!! Non si tiene conto del seme della scala colore in quanto è impossibile la presenza in contemporanea di scale reali con semi diversi !!
