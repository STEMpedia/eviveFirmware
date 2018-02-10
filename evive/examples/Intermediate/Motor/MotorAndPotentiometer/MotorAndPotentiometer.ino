/* this example demonstrates how to use motor with Potentiometer
    atteched in evive
    To use second motor change digit 1 to 2 eg MOTOR1_D1 to MOTOR2_D1

    Created by Nihar Shah
    On 13 Sep, 2017
*/

#include <evive.h>

Motor Motor1 = Motor(MOTOR1_D1, MOTOR1_D2, MOTOR1_EN); // defines motor 1

int potData=0;
void setup() { 
  // put your setup code here, to run once:

}

void loop() {
  potData=analogRead(POT1); // reads pot data between 0 to 1023.
  potData = potData/4;  //motor input range is 0 to 255.
  Motor1.moveMotor(potData);  // writes motor with potentiometer value. 
}
