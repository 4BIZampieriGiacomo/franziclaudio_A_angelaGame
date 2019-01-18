
  //BOTTONI

  //Variabili
  int nVincente = 0;
  int sommaDadiTotale = 0;
  int nGiocatoPrima = 0;
  int stato = 0;
  int turno = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(stato == 0)//Inserimento della variabile da raggiungere per vincere
  {
    primoValore();//Controllo della variabile inquanto deve rispettare determinate caratteristiche
  }
  else if(stato = 1)//Inizio della partita vera e propria
  {
    giocata();
    vittoriaSconfitta();
  }
  else if(stato == 3)//partita finita, resetto le variabili
  {
    
  }
}

void primoValore()//Metodo di Controllo della variabile da raggiungere
{
  if(Serial.available())
  {
    Serial.println("Inserisci un mumero compreso tra 30 e 99");
    int s = Serial.read();
    if(s < 30)
    {
      Serial.println("il numero è troppo piccolo");
    }
    else if(s > 100)
    {
      Serial.println("il numero è troppo grande");
    }
    else
    {
      nVincente = s;
      stato = 1;
    }
  }
}


void giocata()//metodo che gestisce, a turno, l'inserimento del valore dei dadi e li somma 
{
  if(Serial.available())
  {
    Serial.println("Inserisci un mumero compreso tra 1 e 6");
    int d = Serial.read();
    //Se è la prima giocata si può inserire il valore 0 e quindi passare il turno
    nGiocatoPrima == 0 ? (sommaDadiTotale = sommaDadiTotale + d, nGiocatoPrima = 7, turno = turno == 0 ? 1 : 0) :
    (d < 1 ? Serial.println("il numero è troppo piccolo") : (d > 6 ? Serial.println("il numero è troppo grande") : //Se non è la prima giocata controlla prima se è compreso tra 1 e 6
    (d == 1 && nGiocatoPrima == 6 || d == 6 && nGiocatoPrima == 1 || //Se è compreso tra 1 e 6 controlla se il numero rispecchia le condizioni adatte
    d == 2 && nGiocatoPrima == 5 || d == 5 && nGiocatoPrima == 2 || 
    d == 3 && nGiocatoPrima == 4 || d == 4 && nGiocatoPrima == 3)
    ? Serial.println("non puoi usare questo valore") : (sommaDadiTotale = sommaDadiTotale + d, nGiocatoPrima = d, turno = turno == 0 ? 1 : 0)));
  }
}

void vittoriaSconfitta()//metodo che definisce chi ha vinto e chi ha perso una volta raggiunte determinate condizioni
{
  nVincente == sommaDadiTotale ? ((turno == 0 ? (Serial.println("Il giocatore 1 ha vinto!!!"),stato = 3) : (Serial.println("Il giocatore 2 ha vinto!!!"),stato = 3)))
  :(nVincente < sommaDadiTotale ? (turno == 0 ? (Serial.println("Il giocatore 1 ha perso!!!"),stato = 3) : (Serial.println("Il giocatore 2 ha perso!!!"),stato = 3)) 
  : (sommaDadiTotale = sommaDadiTotale));
}
