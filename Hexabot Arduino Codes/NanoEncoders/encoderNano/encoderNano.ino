
#include <Encoder.h>
Encoder encoderL(2, 4);
Encoder encoderR(3, 5);
unsigned long previousmills = 0, currentmills = 0;
void setup(){
  Serial.begin(115200);
}

long oldPositionL  = -999;
long oldPositionR  = -999;

void loop() {
  unsigned long currentmills = millis();
  long newPositionR = encoderR.read();
  long newPositionL = encoderL.read();
  if (newPositionL != oldPositionL) {
    oldPositionL = newPositionL;
  }
  if (newPositionR != oldPositionR) {
    oldPositionR = newPositionR;
  }
  if (currentmills - previousmills >= 200){
    previousmills = currentmills;
    Serial.print(newPositionR*0.00026928);
    Serial.print("\t");
    Serial.println(newPositionL*0.00026639);
  
  }
  
}
