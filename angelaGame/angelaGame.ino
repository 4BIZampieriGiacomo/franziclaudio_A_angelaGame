
  //BOTTONI

  //Variabili
  int nVincente = 0;//30 <= nVincente <= 99
  int sommaDadiTotale = 0;
  int nGiocatoPrima = 0;//back-up della giocata precedente 
  bool primoTurno = true;
  int stato = 0;//Indica i vari momenti del gioco 
  int turno = 0;// indica i turni dei due giocatori: 0 = Giocatore 1 , 1 = Giocatore 2
  int x = 0;
   

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(stato == 0)//Inserimento della variabile da raggiungere per vincere
  {
    if(x == 0)
    {
      Serial.println("Inserisci un mumero compreso tra 30 e 99 per fissare la meta da raggiungere");
      x = 1;
    }
    primoValore();//Controllo della variabile inquanto deve rispettare determinate caratteristiche
  }
  else if(stato == 1)//Inizio della partita vera e propria
  {
    Serial.println(turno == 0 ? "Turno del giocatore 1" : "Turno del giocatore 2");//Indica il turno in corso
    Serial.println("Inserisci il numero da giocare compreso tra 1 e 6");
    giocata();//Metodo che gestisce i turni e il controllo dei vari inserimenti
    vittoriaSconfitta();//Metodo che controlla ogni turno se si ha raggiunto le condizioni di fine partita e decreta il vincitore/perdente
  }
  else if(stato == 3)//partita finita, resetto le variabili
  {
    nVincente = 0;
    sommaDadiTotale = 0;
    nGiocatoPrima = 0;
    primoTurno = true;
    stato = 0;
    turno = 0;
    x = 0;
  }
}




void primoValore()//Metodo di Controllo della variabile da raggiungere
{
  while(Serial.available() == 0){}
  int s = Serial.parseInt();
  if(s < 30)
  {
    Serial.println("numero inserito: " + String(s));
    Serial.println("il numero è troppo piccolo");
  }
  if(s > 99)
  {
    Serial.println("numero inserito: " + String(s));
    Serial.println("il numero è troppo grande");
  }
  if(s >= 30 && s <= 99)
  {
    Serial.println("numero inserito: " + String(s));
    Serial.println("numero inserito correttamente");
    nVincente = s;
    stato = 1;
  }
  x = 0;
}


void giocata()//metodo che gestisce, a turno, l'inserimento del valore dei dadi e li somma 
{
  while(Serial.available() == 0){}
  int d = Serial.parseInt();
  if(primoTurno == true)
  {
    if(d < 0)
    {
      Serial.println("numero inserito: " + String(d));
      Serial.println("il numero è troppo piccolo");
    }
    else
    {
      if(d > 6)
      {
        Serial.println("numero inserito: " + String(d));
        Serial.println("il numero è troppo grande");
      }
      else
      {
        sommaDadiTotale = sommaDadiTotale + d;
        d == 0 ? nGiocatoPrima = 7 : nGiocatoPrima = d;
        primoTurno = false;
        turno = turno == 0 ? 1 : 0;
        Serial.println("numero inserito: " + String(d));
        
        Serial.println("numero raggiunto: " + String(sommaDadiTotale));
      }
    }
  }
  else
  {
    if(d < 1)
    {
      Serial.println("numero inserito: " + String(d));
      Serial.println("il numero è troppo piccolo");
    }
    else
    {
      if(d > 6)
      {
        Serial.println("numero inserito: " + String(d));
        Serial.println("il numero è troppo grande");
      }
      else
      {
        if(d == nGiocatoPrima)
        {
          Serial.println("numero inserito: " + String(d));
          Serial.println("il numero è già stato utilizzato il turno precedente");
        }
        else
        {
          if(d == 1 && nGiocatoPrima == 6 || d == 6 && nGiocatoPrima == 1 || d == 2 && nGiocatoPrima == 5 || d == 5 && nGiocatoPrima == 2 || d == 3 && nGiocatoPrima == 4 || d == 4 && nGiocatoPrima == 3)
          {
            Serial.println("numero inserito: " + String(d));
            Serial.println("non puoi usare questo valore");
          }
          else
          {
            sommaDadiTotale = sommaDadiTotale + d;
            nGiocatoPrima = d;
            turno = turno == 0 ? 1 : 0;
            Serial.println("numero inserito: " + String(d));
            Serial.println("numero raggiunto: " + String(sommaDadiTotale));
          }
        }
      }
    }
  }
}



void vittoriaSconfitta()//metodo che definisce chi ha vinto e chi ha perso una volta raggiunte determinate condizioni
{
  if(nVincente == sommaDadiTotale)
  {
    if(turno == 0)
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

  if(nVincente < sommaDadiTotale)
  {
    if(turno == 0)
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
