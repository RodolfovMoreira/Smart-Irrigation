#include "Servo.h" 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); 
Servo meuservo; 
  
int numberSensores = 4;
int sensores[4] = {14,15,16,17}; // pino para a entrada do pulso;; A0 , A1, A2, A3
double pointOff[4]= {1.0,1.0,1.0,1.0};// pontos ideais de cada região em relação a frequencia que o sensor captura
int irrigando = 0; // indica se está irrigando ou não
int currentPoint = 0;// ponto que está sendo irrigado 0 ,1 , 2 ,3
int positionsServo[4] = {0,180,130,70}; //angulos de cada região para o servo motor

int bomba = 3; // pino para a entrada da bomba

int getNextPoint(){// calcula o sensor que precisa de agua mais urgente, senso que pode ser nenhum (-1)
  //maior acima de 2
  int pointWin = -1;
  double valuePointWin = 0;
  double current;
  
  for(int i =0; i< numberSensores; i++){
    current = getFrequencyBySensor(sensores[i]);
    if(current > 2 and current > valuePointWin ){
      pointWin = i;
      valuePointWin = current; 
     }  
  }
  return pointWin;
}

double getFrequencyBySensor(int sensor){//pega a frequencia do sensor passado como parametor
  int n = 0;
  double count = 0;
  double duracao; //variável para guardar a duração do pulso
  double arduinoRef = 0;
  while (n<1000){
    duracao = pulseIn(sensor, LOW);
    count = count + duracao;
    arduinoRef =  1000/( (count/1000));  
    n++;
  }
  double freq = 0.85*arduinoRef-2.55;
  return freq;
}

void irrigarOn(){//iniciar irrigação
   irrigando = 1;
   moveServo(currentPoint);
   delay(3000);
   //ligarBomba 
}
void irrigarOff(){//para irrigação
  irrigando = 0;
  //desligarmotor
  delay(3000);  
}
void moveServo(int point){//move o servo para o ponto adequado en relação ao point passado
    meuservo.write(positionsServo[point]);
}

void pumpit(){
  //Vout = (duty cycle/100)*Vcc
  analogWrite(bomba,127); // 50% Duty Cicle
  //5
}

void setup() {
  meuservo.attach(9); // Declara o pino do servo
  lcd.begin (16,2); 
  pinMode(sensores[0], INPUT); // configura pino como entrada
  pinMode(sensores[1], INPUT); // configura pino como entrada
  pinMode(sensores[2], INPUT); // configura pino como entrada
  pinMode(sensores[3], INPUT); // configura pino como entrada
  pinMode(bomba,OUTPUT); // configura pino como saída
  Serial.begin(9600);

}


void loop() {
    if(irrigando == 1){ //estiver irrigando
        double freq = getFrequencyBySensor(sensores[currentPoint]);//pegar a frequencia do sensor do local onde está irrigando

        lcd.setCursor(0,0);
        lcd.print("Regiao "+String(currentPoint+1));
        lcd.setCursor(0,1);
        lcd.print(freq);
        
        if(freq < pointOff[currentPoint]){//verifica se a frequencia é menor do que o nivel ideal de frequencia 
          irrigarOff();//desliga a irrigação
        }
    }
    else{//se não estiver irrigando
      currentPoint = getNextPoint();//pega o proximo ponto para irrigar, 0 1 2 ou 3
      if(currentPoint > -1){//se o valor de getnextponit == -1 quer dizer que não precisa irrigar em canto nenhum
          irrigarOn();//inicia a irrigação   
      }
      Serial.println(currentPoint);
    }
}  
