//motor_A
  int IN1 = 2 ;
  int IN2 = 4 ;
  int velocidadeA = 3;

//variavel auxiliar
  int velocidade = 0;
  int control_s = HIGH;

//Inicializa Pinos
 void setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(velocidadeA,OUTPUT);
 }

void loop(){

/Exemplo de velocidades no motor A/
  control_s = HIGH;
  if(control_s){
  //Sentido 2
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //Baixa
  analogWrite(velocidadeA,80);
  delay(4000);
  }
  control_s = LOW;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  delay(2000);
}