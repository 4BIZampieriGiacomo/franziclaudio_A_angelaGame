#include <LiquidCrystal.h>
//LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//BOTTONI
int b1;//diminuisce
int b2;//conferma
int b3;//aumenta

//Variabili
bool primaAperturaProgramma = true;//evita,durante il richiamo del setup , di inizializzare alcune variabili alla fine di ogni partita
int x;//variabile di controllo
int nVincente;//30 <= nVincente <= 99
int sommaDadiTotale;
int nGiocatoPrima;//back-up della giocata precedente
bool primoTurno;
int stato;//Indica i vari momenti del gioco
int turno;// indica i turni dei due giocatori: 0 = Giocatore 1 , 1 = Giocatore 2
bool winLose;


void setup() {
  if (primaAperturaProgramma)
  {
    lcd.begin(16, 2);
    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    primaAperturaProgramma = false;
  }
  nVincente = 0;
  sommaDadiTotale = 0;
  nGiocatoPrima = 0;
  primoTurno = true;
  stato = 0;
  turno = 0;
  x = 0;
}

void loop() {
  if (stato == 0) //Inserimento della variabile da raggiungere per vincere
  {
    if (x == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Inserisci numero");
      lcd.setCursor(0, 1);
      lcd.print("tra 30 e 99: ");
    }
    nVincente = selectValue(1);//Imposto la meta
    if (nVincente != 0)
    {
      lcd.setCursor(13, 1);
      lcd.print(nVincente);
      delay(1500);
    }
  }
  else if (stato == 1) //Inizio della partita vera e propria
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(turno == 0 ? "Player 1" : "Player 2");//Indica il turno in corso
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.println("Inserisci numero");
    lcd.print("tra 1 e 6: ");
    playerTurn();//Metodo che gestisce i turni
    lcd.clear();
    Serial.println("N° giocato: " + String(nGiocatoPrima));
    Serial.println("Totale: " + String(sommaDadiTotale));
    if (vittoriaSconfitta() != "") //Metodo che controlla ogni turno se si ha raggiunto le condizioni di fine partita e decreta il vincitore/perdente
    {
      Serial.println("Il giocatore" + vittoriaSconfitta() + (winLose ? "ha vinto!!!" : "ha perso!!!"));
    }
  }
  else if (stato == 3) {
    setup();  //partita finita, reset delle variabili
  }
}


//metodo che permette in base alla fase del gioco di impostare la meta o il numero del dado giocato
int selectValue(int condiz)
{
  bool finish = false;
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
  lcd.setCursor(13, 1);
  lcd.print(value);

  while (finish)
  {
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
      lcd.setCursor(13, 1);
      lcd.print(value);
    }

    //conferma
    if (b2 == LOW) {
      finish = true;
      return value;
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
      lcd.setCursor(13, 1);
      lcd.print(value);
    }
  }
}

//Metodo che dopo l'inserimento del numero del dado effettua la somma totale e cambia il turno
void playerTurn()
{
  if (primoTurno == true)
  {
    int n = selectValue(2);
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    primoTurno = false;
    turno = turno == 0 ? 1 : 0;
  }
  else
  {
    int n = selectValue(3);
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
