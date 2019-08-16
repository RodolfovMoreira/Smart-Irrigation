 
#include "Servo.h" 
 
Servo meuservo; 

int angulo = 0;  
int pino = 14; //pino para a entrada do pulso

void quartoquadrante(){
  delay(10000);
  meuservo.write(70);
}

void terceiroquadrante(){
  delay(10000);
  meuservo.write(0);
}

void primeiroquadrante(){
  delay(10000);
  meuservo.write(130);
}

void segundoquadrante(){
  delay(10000);
  meuservo.write(180);
}
 
void setup() {
  meuservo.attach(9); // Declara o pino do servo

  Serial.begin(9600);
  pinMode(pino, INPUT);
}

int leitura(){
  int n = 0;
  double count = 0;
  double duracao; //variável para guardar a duração do pulso

  duracao = pulseIn(pino, LOW);
  count = count + duracao;
  n++;
  if(n>1000){
    Serial.print("media ");
    double arduinoRef =  1000/( (count/1000));
    Serial.println(0.85*arduinoRef-2.55);  
    n = 0;
    count =0;
    delay(1000);
  }
}


void loop() { 

  // LÓGICA PARA ATIVAÇÃO DEPENDENDO DOS VALORES LIDOS VAI AQUI

}  
