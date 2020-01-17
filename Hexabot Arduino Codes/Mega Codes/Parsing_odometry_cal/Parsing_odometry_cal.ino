#define EN_L 9
#define IN1_L 25
#define IN2_L 24

#define EN_R 8
#define IN1_R 22
#define IN2_R 23

void Motors_init();
void MotorL(int Pulse_Width1);
void MotorR(int Pulse_Width2);


String command_ultra, command_encoders;
int ultraL1, ultraL2, ultraR1, ultraR2, ultraF, ultraB;
long encoderL, encoderR;
String part1_ultra, part2_ultra, part3_ultra, part4_ultra, part5_ultra, part6_ultra;
String part1_encoders, part2_encoders;
char c_ultra, c_encoders;
unsigned long previousmills = 0, currentmills = 0;
const long interval = 200;


/*-------------------Functions init---------------------*/
int count = 0;
void r_ultra();
void r_encoders();
void parse_ultra(String command_ultra1);
void parse_encoders(String command_encoders1);
void t_data1();
void from_dxdy_to_xytheta(long pos_l, long pos_r);

double theta=0, x=0, y=0;
/*---------------------Main code------------------------*/
// Ultrasonics Nano on Serial 3
// Encoders Nano on Serial 2
// Raspberry pi on Serial 1


void setup(){
  Motors_init();
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  MotorL(200);
  MotorR(200);
  delay(1000);
  MotorL(0);
  MotorR(0);
}



void loop() {
  unsigned long currentmills = millis();
  r_ultra();
  r_encoders();
  from_dxdy_to_xytheta(encoderL, encoderR);
  if (currentmills - previousmills >= interval){
    previousmills = currentmills;
    Serial.print(encoderL);
    Serial.print("\t");
    Serial.print(encoderR);
    Serial.print("\t");
    Serial.println(theta);
  }
  
  
}

























/*------------------------------------Functions---------------------------------*/

//receiving from ultrasonics
void r_ultra(){
  if (Serial3.available()) {
    c_ultra = Serial3.read();

    if (c_ultra == '\n') {
      parse_ultra(command_ultra);
      command_ultra = "";
    }
    else {
      command_ultra += c_ultra;
    }
  }
}



//receiving from encoders
void r_encoders(){
  if (Serial2.available()) {
    c_encoders = Serial2.read();

    if (c_encoders == '\n') {
      parse_encoders(command_encoders);
      command_encoders = "";
    }
    else {
      command_encoders += c_encoders;
    }
  }
}



//parse Ultrasonic data
void parse_ultra(String command_ultra1){
  part1_ultra = command_ultra1.substring(0, command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part2_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part3_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part4_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part5_ultra = command_ultra1.substring(0, command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part6_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\n"));
  
  ultraL1 = part1_ultra.toFloat();
  ultraL2 = part2_ultra.toFloat();
  ultraR1 = part3_ultra.toFloat();
  ultraR2 = part4_ultra.toFloat();
  ultraF = part5_ultra.toFloat();
  ultraB = part6_ultra.toFloat();
}



//parse GPS data
void parse_encoders(String command_encoders1){
  part1_encoders = command_encoders1.substring(0, command_encoders1.indexOf("\t"));
  command_encoders1.remove(0, command_encoders1.indexOf("\t")+1);
  part2_encoders = command_encoders1.substring(0,command_encoders1.indexOf("\n"));
  
  encoderL = part1_encoders.toFloat();
  encoderR = part2_encoders.toFloat();
}

void t_data(){
  
  Serial.print(ultraL1);        //1
  Serial.print("\t");
  
  Serial.print(ultraL2);         //2
  Serial.print("\t");
  
  Serial.print(ultraR1);        //3
  Serial.print("\t");
  
  Serial.print(ultraR2);        //4
  Serial.print("\t");
  
  Serial.print(ultraF);        //5
  Serial.print("\t");
  
  Serial.print(ultraB);        //6
  Serial.print("\t");
  
  Serial.print(encoderL);        //7
  Serial.print("\t");
  
  Serial.print(encoderR);        //8  
  Serial.println();
}

void from_dxdy_to_xytheta(long pos_l, long pos_r){
  theta = (1/0.29)*(pos_r-pos_l)*(1/1000.0);
  x = 0.5*(pos_l+pos_r)*cos(theta);
  y = 0.5*(pos_l+pos_r)*sin(theta);
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


