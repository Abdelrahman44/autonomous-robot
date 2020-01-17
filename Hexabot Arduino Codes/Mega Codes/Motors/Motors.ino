#define EN_L 9
#define IN1_L 25
#define IN2_L 24

#define EN_R 8
#define IN1_R 22
#define IN2_R 23

void Motors_init();
void MotorL(int Pulse_Width1);
void MotorR(int Pulse_Width2);
void setup() {
  Motors_init();
}

void loop() {
  MotorL(200);
  MotorR(200);
  /*
  delay(2000);
  MotorL(100);
  MotorR(100);
  delay(2000);
  
  delay(2000);
  */

}



void Motors_init(){
  pinMode(EN_L, OUTPUT);
  pinMode(EN_R, OUTPUT);
  pinMode(IN1_L, OUTPUT);
  pinMode(IN2_L, OUTPUT);
  pinMode(IN1_R, OUTPUT);
  pinMode(IN2_R, OUTPUT);
  digitalWrite(EN_L, LOW);
  digitalWrite(EN_R, LOW);
  digitalWrite(IN1_L, LOW);
  digitalWrite(IN2_L, LOW);
  digitalWrite(IN1_R, LOW);
  digitalWrite(IN2_R, LOW);
}


void MotorL(int Pulse_Width1){
  
  if (Pulse_Width1 > 0){
      analogWrite(EN_L, Pulse_Width1);
      digitalWrite(IN1_L, HIGH);
      digitalWrite(IN2_L, LOW);
  }
  if (Pulse_Width1 < 0){
      Pulse_Width1=abs(Pulse_Width1);
      analogWrite(EN_L, Pulse_Width1);
      digitalWrite(IN1_L, LOW);
      digitalWrite(IN2_L, HIGH);
  }
  if (Pulse_Width1 == 0){
      analogWrite(EN_L, Pulse_Width1);
      digitalWrite(IN1_L, LOW);
      digitalWrite(IN2_L, LOW);
  }
}

void MotorR(int Pulse_Width2){
  
  if (Pulse_Width2 > 0){
      analogWrite(EN_R, Pulse_Width2);
      digitalWrite(IN1_R, LOW);
      digitalWrite(IN2_R, HIGH);
  }
  if (Pulse_Width2 < 0){
      Pulse_Width2=abs(Pulse_Width2);
      analogWrite(EN_R, Pulse_Width2);
      digitalWrite(IN1_R, HIGH);
      digitalWrite(IN2_R, LOW);
  }
  if (Pulse_Width2 == 0){
      analogWrite(EN_R, Pulse_Width2);
      digitalWrite(IN1_R, LOW);
      digitalWrite(IN2_R, LOW);
  }
}
