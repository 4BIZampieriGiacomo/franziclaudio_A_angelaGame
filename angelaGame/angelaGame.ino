
  //BOTTONI
  int buttonPin1 = 10;
  int buttonPin2 = 11;
  int buttonPin3 = 12;

  //Variabili
  int n = 50;
  int stato = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


void impostaPrimoValore()
{
  if(stato == 0)
  {
    if (digitalRead(buttonPin1) == LOW)
    {
      if(n >= 30)
      {
        n--;
      }
    }

    if(digitalRead(buttonPin3) == LOW)
    {
      if(n < 100)
      {
        n++;
      }
    }
  }
}
