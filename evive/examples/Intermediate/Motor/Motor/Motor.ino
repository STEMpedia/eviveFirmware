/*
   evive motor control through motor library

   For Motor 1: Dirction digital pins are MOTOR1_D1 and MOTOR1_D2, and PWM pin is digital pin MOTOR1_EN
   For Motor 2: Dirction digital pins are MOTOR2_D1 and MOTOR2_D2, and PWM pin is digital pin MOTOR2_EN

   This code demonstrate how to use motor library, intialise motor, and controlling motor.

   Created by Nihar Shah
   On 13 Sep, 2017
*/

#include <evive.h>
Motor Motor1 = Motor(MOTOR1_D1, MOTOR1_D2, MOTOR1_EN);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  
  //Rotate motor in CW direction with PWM 150
  Motor1.moveMotor(150);
  delay(1000);
  
  // Stop Motor
  Motor1.freeMotor();
  delay(1000);
  
  // Rotate motor in CCW direction with PWM -150
  Motor1.moveMotor(-150);
  delay(1000);

  // Stop Motor
  Motor1.freeMotor();
  delay(1000);
}
