/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder encoderL(2, 4);
Encoder encoderR(3, 5);

//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPositionL  = -999;
long oldPositionR  = -999;

void loop() {
  long newPositionR = encoderR.read();
  long newPositionL = encoderL.read();
  if (newPositionL != oldPositionL) {
    oldPositionL = newPositionL;
  }
  if (newPositionR != oldPositionR) {
    oldPositionR = newPositionR;
  }
  Serial.print(newPositionR);
  Serial.print("\t");
  Serial.println(newPositionL);
}
