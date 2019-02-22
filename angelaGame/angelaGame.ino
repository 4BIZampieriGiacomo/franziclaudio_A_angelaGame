#include <LiquidCrystal.h>
//LCD
LiquidCrystal lcd(12,11,10,9,8,7);

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


void setup() {
  if(primaAperturaProgramma)
  {
    Serial.begin(9600);
    lcd.begin(0,0);
    pinMode(b1,INPUT_PULLUP);
    pinMode(b2,INPUT_PULLUP);
    pinMode(b3,INPUT_PULLUP);
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
      Serial.println("Inserisci un mumero compreso tra 30 e 99 per fissare la meta da raggiungere");
      x = 1;
    }
    
    nVincente = selectValue(1);
    //primoValore();//Controllo della variabile inquanto deve rispettare determinate caratteristiche
  }
  else if (stato == 1) //Inizio della partita vera e propria
  {
    Serial.println(turno == 0 ? "Turno del giocatore 1" : "Turno del giocatore 2");//Indica il turno in corso
    Serial.println("Inserisci il numero da giocare compreso tra 1 e 6");
    //giocata();//Metodo che gestisce i turni e il controllo dei vari inserimenti
    playerTurn();
    vittoriaSconfitta();//Metodo che controlla ogni turno se si ha raggiunto le condizioni di fine partita e decreta il vincitore/perdente
  }
  else if (stato == 3) //partita finita, resetto le variabili
  {
    setup();
  }
}


//metodo che permette in base alla fase del gioco di impostare la meta o il numero del dado giocato
int selectValue(int condiz)
{
  int value;
  bool c1 = value <= 99 && value >= 30;//condizione da rispettare per impostare la meta
  bool c2 = value != (7 - nGiocatoPrima) && value < 7 && value >= 0;
  bool c3 = value != nGiocatoPrima && value != (7 - nGiocatoPrima) && value < 7 && value > 0;//condizione da rispettare per l'inserimento del numero del dado
  
  //assegnazione valore base
  if(condiz == 1)
  {
    value = 30;
  }
  if(condiz = 2)
  {
    value = 0;
  }
  if(condiz = 3)
  {
    value = 1;
  }

  
  //diminuisce
  if(b1 == LOW)
  {
    if(condiz == 1)
    {
      value--;
      if(!c1)
      {
        value++;
      }
    }
    if(condiz == 2)
    {
      value--;
      if(!c2)
      {
        value++;
      }
    }
    if(condiz == 3)
    {
      value--;
      if(!c3)
      {
        value++;
      }
    }
  }

  //conferma
  if(b2 == LOW)
  {
    return value;
  }

  //aumenta
  if(b3 == LOW)
  {
     if(condiz == 1)
    {
      value++;
      if(!c1)
      {
        value--;
      }
    }
    if(condiz == 2)
    {
      value++;
      if(!c2)
      {
        value--;
      }
    }
    if(condiz == 3)
    {
      value--;
      if(!c3)
      {
        value++;
      }
    }
  }
}

//void primoValore()//Metodo di Controllo della variabile da raggiungere
//{
  //while (Serial.available() == 0) {}
  //int s = Serial.parseInt();
  //if (s < 30)
  //{
    //Serial.println("il numero: " + String(s) + " è troppo piccolo");
  //}
  //if (s > 99)
  //{
    //Serial.println("il numero: " + String(s) + " è troppo grande");
  //}
  //if (s >= 30 && s <= 99)
  //{
    //Serial.println("il numero: " + String(s) + " è stato inserito correttamente");
    //nVincente = s;
    //stato = 1;
  //}
  //x = 0;
//}


//void giocata()//metodo che gestisce, a turno, l'inserimento del valore dei dadi e li somma
//{
  //while (Serial.available() == 0) {}
  //int d = Serial.parseInt();
  //if (primoTurno == true)
  //{
    //if (d < 0)
    //{
      //Serial.println("il numero: " + String(d) + " è troppo piccolo");
    //}
    //else
    //{
      //if (d > 6)
      //{
        //Serial.println("il numero: " + String(d) + " è troppo grande");
      //}
      //else
      //{
        //sommaDadiTotale = sommaDadiTotale + d;
        //d == 0 ? nGiocatoPrima = 7 : nGiocatoPrima = d;
        //primoTurno = false;
        //turno = turno == 0 ? 1 : 0;
        //Serial.println("numero raggiunto: " + String(sommaDadiTotale));
      //}
    //}
  //}
  //else
  //{
    //if (d < 1)
    //{
      //Serial.println("il numero: " + String(d) + " è troppo piccolo");
    //}
    //else
    //{
      //if (d > 6)
      //{
        //Serial.println("il numero: " + String(d) + " è troppo grande");
      //}
      //else
      //{
        //if (d == nGiocatoPrima)
        //{
          //Serial.println("il numero inserito: " + String(d) + " è già stato utilizzato il turno precedente");
        //}
        //else
        //{
          //if (d == 1 && nGiocatoPrima == 6 || d == 6 && nGiocatoPrima == 1 || d == 2 && nGiocatoPrima == 5 || d == 5 && nGiocatoPrima == 2 || d == 3 && nGiocatoPrima == 4 || d == 4 && nGiocatoPrima == 3)
          //{
            //Serial.println("il numero inserito: " + String(d) + "non può essere utilizzato");
          //}
          //else
          //{
            //sommaDadiTotale = sommaDadiTotale + d;
            //nGiocatoPrima = d;
            //turno = turno == 0 ? 1 : 0;
            //Serial.println("numero raggiunto: " + String(sommaDadiTotale));
          //}
        //}
      //}
    //}
  //}
//}


void playerTurn()
{
  if (primoTurno == true)
  {
    int n = selectValue(2);
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    primoTurno = false;
    turno = turno == 0 ? 1 : 0;
    //Serial.println("numero raggiunto: " + String(sommaDadiTotale));
  }
  else
  {
    int n = selectValue(3);
    sommaDadiTotale = sommaDadiTotale + n;
    nGiocatoPrima = n;
    turno = turno == 0 ? 1 : 0;
    //Serial.println("numero raggiunto: " + String(sommaDadiTotale));
  }
}


void vittoriaSconfitta()//metodo che definisce chi ha vinto e chi ha perso una volta raggiunte determinate condizioni
{
  if (nVincente == sommaDadiTotale)
  {
    if (turno == 0)
    {
      Serial.println("Il giocatore 2 ha vinto!!!");
      stato = 3;
    }
    else
    {
      Serial.println("Il giocatore 1 ha vinto!!!");
      stato = 3;
    }
  }

  if (nVincente < sommaDadiTotale)
  {
    if (turno == 0)
    {
      Serial.println("Il giocatore 2 ha perso!!!");
      stato = 3;
    }
    else
    {
      Serial.println("Il giocatore 1 ha perso!!!");
      stato = 3;
    }
  }
}
