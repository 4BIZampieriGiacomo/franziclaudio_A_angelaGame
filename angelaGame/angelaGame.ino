#include <LiquidCrystal.h>
//LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//BOTTONI
const int b1 = 4;   //diminuisce
const int b2 = 5;   //conferma
const int b3 = 6;   //aumenta

//Variabili
bool primaAperturaProgramma = true;       //evita,durante il richiamo del setup , di inizializzare alcune variabili alla fine di ogni partita
int x;                                    //variabile di controllo
int nVincente;                            //meta che decreta la fine della partita
int sommaDadiTotale;                      //indica il valore della somma di tutti i valori giocati
int nGiocatoPrima;                        //back-up della giocata precedente
bool primoTurno;                          //indica se il turno in corso è il primo della partita
int stato;                                //Indica i vari momenti del gioco
int turno;                                // indica i turni dei due giocatori: 0 = Giocatore 1 , 1 = Giocatore 2
bool winLose;                             //indica se ha vinto o perso
int delayBase;                            //variabile impostata di base per tutti i delay
bool decisioneMeta;                       //indica se l'utente ha confermato la scelta della meta
bool setBaseValue;
bool decisioneGiocata;                    //indica se l'utente ha confermato la scelta della giocata
int nGiocato;


void setup() {
  if (primaAperturaProgramma)
  {
    //variabili che non devono essere resettate al riavvio della partita
    lcd.begin(16, 2);
    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    primaAperturaProgramma = false;
    delayBase = 2000;
  }

  //variabili che vengono resettate a fine partita
  nVincente = 0;
  sommaDadiTotale = 0;
  nGiocatoPrima = 0;
  primoTurno = true;
  decisioneMeta = false;
  decisioneGiocata = false;
  stato = 0;
  turno = 0;
  x = 0;
  setBaseValue = false;
  nGiocato = 0;
}

void loop() {
  if (stato == 0)       //Inserimento della variabile da raggiungere per vincere
  {
    if (x == 0)
    {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("*** ANGELA ***");
      lcd.setCursor(1, 1);
      lcd.print("***  GAME  ***");
      delay(delayBase * 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Inserisci numero");
      lcd.setCursor(0, 1);
      lcd.print("tra 30 e 99: ");
    }

    //Imposto la meta
    while (!decisioneMeta)
    {
      nVincente = selectValue(1);
      lcd.setCursor(13, 1);
      lcd.print(nVincente);
      delay(delayBase / 6);
    }
  }
  else if (stato == 1)        //Inizio della partita vera e propria
  {
    //indico che giocatore deve giocare
    lcd.clear();
    String x;
    String y;
    if (turno == 0)
    {
      x = "Turno del";
      y = "giocatore 1";
    }
    else
    {
      x = "Turno del";
      y = "giocatore 2";
    }
    lcd.setCursor(3, 0);
    lcd.print(x);
    lcd.setCursor(3, 1);
    lcd.print(y);
    delay(delayBase);

    //procedo con l'inserimento del numero da giocare
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Inserisci numero");
    lcd.setCursor(0, 1);
    lcd.print("tra 1 e 6: ");
    while (!decisioneGiocata)
    {
      int c = primoTurno == true ? 2 : 3;
      nGiocato = selectValue(c);
      lcd.setCursor(12, 1);
      lcd.print(nGiocato);
      delay(delayBase / 6);
    }

    //riporto la somma e cambio il turno
    playerTurn(nGiocato);
    decisioneGiocata = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("N. giocato: " + String(nGiocatoPrima));
    lcd.setCursor(0, 1);
    lcd.print("Totale: " + String(sommaDadiTotale));
    delay(delayBase);

    //controllo ogni turno se si ha raggiunto le condizioni di fine partita e decreta il vincitore/perdente
    if ((nVincente == sommaDadiTotale) || (nVincente < sommaDadiTotale))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      String a = "*il giocatore " + vittoriaSconfitta() + "*";
      lcd.print(a);
      lcd.setCursor(0, 1);
      String s;
      if (winLose)
      {
        s = "*  ha vinto!!  *";
      }
      else
      {
        s = "*  ha perso!!  *";
      }
      lcd.print(s);
      delay(delayBase * 2);
      stato = 3;
    }
  }
  else if (stato == 3) {
    setup();  //partita finita, reset delle variabili
  }
}


//metodo che permette in base alla fase del gioco di impostare la meta o il numero del dado giocato
int selectValue(int condiz)
{
  int value = condiz == 1 ? nVincente : nGiocato;
  int opposto = 7 - nGiocatoPrima;

  //assegnazione valore base
  if (!setBaseValue)
  {
    if (condiz == 1) {
      value = 50;
    }
    if (condiz == 2) {
      value = 3;
    }
    if (condiz == 3) {
      if (nGiocatoPrima == 3)
      {
        value = 1;
      }
      else
      {
        value = 3;
      }
    }
    setBaseValue = true;
  }

  bool choice = false;
  while (!choice)
  {
    //diminuisce
    if (digitalRead(b1) == LOW)
    {
      if (condiz == 1 && value == 30)//se va sotto il range va al numero masimo
      {
        value = 99;
      }
      else if ((condiz == 2 && value == 0) || (condiz == 3 && value == 1))//se va sotto il range va al numero masimo
      {
        value = 6;
      }
      else if (condiz == 3 && (nGiocatoPrima == 6 || opposto == 6) && value == 2)
      {
        value = 5;
      }
      else if (condiz == 3 && (nGiocatoPrima == 3 || opposto == 3) && value == 5)
      {
        value = 2;
      }
      else if (condiz == 3 && (value - 1 == nGiocatoPrima || value - 1 == opposto))
      {
        value = value - 2;
      }
      else
      {
        value--;
      }
      choice = true;
    }

    //conferma
    if (digitalRead(b2) == LOW)
    {
      if (stato == 0)
      {
        decisioneMeta = true;
      }
      else if (stato == 1)
      {
        decisioneGiocata = true;
      }
      setBaseValue = false;
      choice = true;
      if (stato == 0)
      {
        stato = 1;
      }
    }

    //aumenta
    if (digitalRead(b3) == LOW)
    {
      if (condiz == 1 && value == 99)
      {
        value = 30;
      }
      else if (condiz == 2 && value == 6)
      {
        value = 0;
      }
      else if (condiz == 3 && value == 6)
      {
        value = 1;
      }
      else if (condiz == 3 && (nGiocatoPrima == 1 || opposto == 1) && value == 5)
      {
        value = 2;
      }
      else if (condiz == 3 && (nGiocatoPrima == 4 || opposto == 4) && value == 2)
      {
        value = 5;
      }
      else if (condiz == 3 && (value + 1 == nGiocatoPrima || value + 1 == opposto))
      {
        value = value + 2;
      }
      else
      {
        value++;
      }
      choice = true;
    }
  }
  return value;
}

//Metodo che dopo l'inserimento del numero del dado effettua la somma totale e cambia il turno
void playerTurn(int n)
{
  if (primoTurno == true)
  {
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    primoTurno = false;
    turno = turno == 0 ? 1 : 0;
  }
  else
  {
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    turno = turno == 0 ? 1 : 0;
  }
}

//metodo che definisce chi ha vinto e chi ha perso una volta raggiunte determinate condizioni
String vittoriaSconfitta()
{
  if (nVincente == sommaDadiTotale)
  {
    if (turno == 0)
    {
      winLose = true;
      return "2";
    }
    else
    {
      winLose = true;
      return "1";
    }
  }
  else if (nVincente < sommaDadiTotale)
  {
    if (turno == 0)
    {
      winLose = false;
      return "2";
    }
    else
    {
      winLose = false;
      return "1";
    }
  }
  else
  {
    return "";
  }
}
