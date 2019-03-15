#include <LiquidCrystal.h>
//LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//BOTTONI
int b1;   //diminuisce
int b2;   //conferma
int b3;   //aumenta

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
bool decisioneGiocata;                    //indica se l'utente ha confermato la scelta della giocata


void setup() {
  if (primaAperturaProgramma)
  {
    //variabili che non devono essere resettate al riavvio della partita
    lcd.begin(16, 2);
    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    primaAperturaProgramma = false;
    delayBase = 1500;
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
}

void loop() {
  if (stato == 0)       //Inserimento della variabile da raggiungere per vincere
  {
    if (x == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Inserisci numero");
      lcd.setCursor(0, 1);
      lcd.print("tra 30 e 99: ");
    }

    //Imposto la meta
    while (decisioneMeta)
    {
      nVincente = selectValue(1);
      if (nVincente != 0)
      {
        lcd.setCursor(13, 1);
        lcd.print(nVincente);
        delay(delayBase);
      }
    }
  }
  else if (stato == 1)        //Inizio della partita vera e propria
  {
    //indico che giocatore deve giocare
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(turno == 0 ? "Player 1" : "Player 2");
    delay(delayBase);

    //procedo con l'inserimento del numero da giocare
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Inserisci numero");
    lcd.setCursor(0, 1);
    lcd.print("tra 1 e 6: ");
    int nGiocato;
    while(decisioneGiocata)
    {
      nGiocato = selectValue(primoTurno == true ? 2 : 3);
      lcd.setCursor(12,1);
      lcd.print(nGiocato);
      delay(delayBase);
    }

    //riporto la somma e cambio il turno
    playerTurn(nGiocato);
    decisioneGiocata == false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("N° giocato: " + String(nGiocatoPrima));
    lcd.setCursor(0, 1);
    lcd.println("Totale: " + String(sommaDadiTotale));
    delay(delayBase);
    //Serial.println("N° giocato: " + String(nGiocatoPrima));
    //Serial.println("Totale: " + String(sommaDadiTotale));

    //controllo ogni turno se si ha raggiunto le condizioni di fine partita e decreta il vincitore/perdente
    if (vittoriaSconfitta() != "") 
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.println("Il giocatore " + vittoriaSconfitta());
      lcd.setCursor(3, 1);
      lcd.println(winLose ? "ha vinto!!" : "ha perso!!");
      //Serial.println("Il giocatore " + vittoriaSconfitta() + (winLose ? "ha vinto!!!" : "ha perso!!!"));
      delay(delayBase);
    }
  }
  else if (stato == 3) {
    setup();  //partita finita, reset delle variabili
  }
}


//metodo che permette in base alla fase del gioco di impostare la meta o il numero del dado giocato
int selectValue(int condiz)
{
  //bool finish = false;
  int value;
  bool case1 = value <= 99 && value >= 30;//condizione da rispettare per impostare la meta
  bool case2 = value != (7 - nGiocatoPrima) && value < 7 && value >= 0;//condizione da rispettare per l'inserimento del numero del dado se è il primo turno
  bool case3 = value != nGiocatoPrima && value != (7 - nGiocatoPrima) && value < 7 && value > 0;//condizione da rispettare per l'inserimento del numero del dado

  //assegnazione valore base
  if (condiz == 1) {
    value = 30;
  }
  if (condiz == 2) {
    value = 0;
  }
  if (condiz == 3) {
    value = 1;
  }
  //lcd.setCursor(13, 1);
  //lcd.print(value);

  //while (finish)
  //{
  //diminuisce
  if (b1 == LOW)
  {
    if (condiz == 1)
    {
      value--;
      if (!case1) {
        value++;
      }
    }
    if (condiz == 2)
    {
      value--;
      if (!case2) {
        value++;
      }
    }
    if (condiz == 3)
    {
      value--;
      if (!case3) {
        value++;
      }
    }
    //lcd.setCursor(13, 1);
    //lcd.print(value);
  }

  //conferma
  if (b2 == LOW) {
    //finish = true;
    //return value;
    condiz == 1 ? decisioneMeta = true : decisioneGiocata = true;
  }

  //aumenta
  if (b3 == LOW)
  {
    if (condiz == 1)
    {
      value++;
      if (!case1) {
        value--;
      }
    }
    if (condiz == 2)
    {
      value++;
      if (!case2) {
        value--;
      }
    }
    if (condiz == 3)
    {
      value++;
      if (!case3) {
        value--;
      }
    }
    //lcd.setCursor(13, 1);
    //lcd.print(value);
  }
  //}

  return value;
}

//Metodo che dopo l'inserimento del numero del dado effettua la somma totale e cambia il turno
void playerTurn(int n)
{
  if (primoTurno == true)
  {
    //int n = selectValue(2);
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    primoTurno = false;
    turno = turno == 0 ? 1 : 0;
  }
  else
  {
    //int n = selectValue(3);
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
      return 2;
    }
    else
    {
      winLose = true;
      return 1;
    }
    stato = 3;
  }
  else if (nVincente < sommaDadiTotale)
  {
    if (turno == 0)
    {
      winLose = false;
      return 2;
    }
    else
    {
      winLose = false;
      return 1;
    }
    stato = 3;
  }
  else
  {
    return "";
  }
}
