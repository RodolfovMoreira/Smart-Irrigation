int pino = 14;           //pino para a entrada do pulso

int n = 0;
double count = 0;

 double duracao; //variável para guardar a duração do pulso

void setup()
{
  Serial.begin(9600);
  pinMode(pino, INPUT);
}

void loop()
{
  duracao = pulseIn(pino, LOW);
  count = count + duracao;
  n++;
//  Serial.println(duracao);  
  if(n>1000){
    Serial.print("media ");
    double arduinoRef =  1000/( (count/1000));
    Serial.println(0.85*arduinoRef-2.55);  
    n = 0;
    count =0;
    delay(1000);
  }
 
}
