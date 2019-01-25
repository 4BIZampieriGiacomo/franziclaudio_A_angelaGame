
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
      Serial.println("Inserisci un mumero compreso tra 30 e 99");
      x = 1;
    }
    //int a = Serial.read();
    primoValore();//Controllo della variabile inquanto deve rispettare determinate caratteristiche
  }
  else if(stato = 1)//Inizio della partita vera e propria
  {
    if(x = 0)
    {
      turno == 0 ? Serial.println("Turno del giocatore 1") : Serial.println("Turno del giocatore 2");//Indica il turno in corso
      Serial.println("Inserisci il numero da giocare compreso tra 1 e 6");
    }
    //int b = Serial.read();
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
  }
}




void primoValore()//Metodo di Controllo della variabile da raggiungere
{
  int s = Serial.read();
  if(Serial.available())
  {
    if(s < 30)
    {
      Serial.println("il numero è troppo piccolo");
    }
    else if(s > 99)
    {
      Serial.println("il numero è troppo grande");
    }
    else
    {
      nVincente = s;
      stato = 1;
      x = 0;
    }
  }
}


void giocata()//metodo che gestisce, a turno, l'inserimento del valore dei dadi e li somma 
{
  int d = Serial.read();
  if(Serial.available())
  {
    primoTurno == true ?  
    //Se è la prima mossa:
    //Verifica se il numero è compreso tra 0 e 6
    ((d < 0 ? Serial.println("il numero è troppo piccolo") : (d > 6 ? Serial.println("il numero è troppo grande") :
     
    //Se è compreso tra 0 e 6 
    (sommaDadiTotale = sommaDadiTotale + d, nGiocatoPrima = 7, primoTurno = false,turno = turno == 0 ? 1 : 0)))) : 

     
    //Se non è la prima mossa:
    //Verifica se il numero è compreso tra 1 e 6: effettua la somma, setta la mossa corrente come mossa giocata il turno precedente, cambia il turno e setta "false" la variabile che indica il primo turno
    (d < 1 ? Serial.println("il numero è troppo piccolo") : (d > 6 ? Serial.println("il numero è troppo grande") : 
    
    //Dopo di chè controlla se è gia stato utilizzato il turno precedente
    (d == nGiocatoPrima ? Serial.println("il numero è già stato utilizzato il turno precedente") : 
    
    //Come ultima procedura controlla se il numero non corrisponde alla faccia opposta del dado del numero giocato il turno precedente
    (d == 1 && nGiocatoPrima == 6 || 
     d == 6 && nGiocatoPrima == 1 || 
     d == 2 && nGiocatoPrima == 5 || 
     d == 5 && nGiocatoPrima == 2 || 
     d == 3 && nGiocatoPrima == 4 || 
     d == 4 && nGiocatoPrima == 3) ? Serial.println("non puoi usare questo valore") : 
     
     //Se il numero ha soddisfatto tutte le condizioni effettua la somma, setta la mossa corrente come mossa giocata il turno precedente, cambia il turno
     (sommaDadiTotale = sommaDadiTotale + d, nGiocatoPrima = d, turno = turno == 0 ? 1 : 0))));
  }
}

void vittoriaSconfitta()//metodo che definisce chi ha vinto e chi ha perso una volta raggiunte determinate condizioni
{
  //Se il numero impostato a inizio partita corrisponde alla somma decreta chi ha vinto in base al turno corrente
  //N.B.: Nonostante il turno sia 0 vince il giocatore 2 perchè il tunro è stato cambiato alla fine del metodo precedente e pertanto sono stati invertiti i vincitori/perdenti
  nVincente == sommaDadiTotale ? ((turno == 0 ? (Serial.println("Il giocatore 2 ha vinto!!!"),stato = 3) : (Serial.println("Il giocatore 1 ha vinto!!!"),stato = 3)))

  //Se il numero impostato a inizio partita è stato superato il giocatore che ha effettuato l'ultima mossa e quindi che ha superato il valore limite perde
  :(nVincente < sommaDadiTotale ? (turno == 0 ? (Serial.println("Il giocatore 2 ha perso!!!"),stato = 3) : (Serial.println("Il giocatore 1 ha perso!!!"),stato = 3))
  
  //Se non rispecchia le precedenti situazioni non fa nulla(il "sommaDadiTotale = sommaDadiTotale" serve per completare le condizioni per usare l'operatore "?")
  : (sommaDadiTotale = sommaDadiTotale));
}
