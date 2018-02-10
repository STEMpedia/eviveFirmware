/*
  evive Bluetooth Setup

  An example of using the evive to Setup HC-05 Bluetooth.
  This Example Changes bluetooth Name to evive,
  Password to 0000 and Baud Rate to default 9600 with no stop bit and no parity bits.
  After this process pin 13 LED glows that shows that process is done.

  modified 12 Sep 2017
  by Nihar Shah

  This example code is in the public domain.
*/
//#include<evive.h>
bool response = 0;
String data = "0";
void setup() {
  // initialize Serial3 communication of bluetooth which is on Serial3 3:
  // bluetoth setup is done at 38400 baud with New line and Carriage Return
  Serial3.begin(38400);
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
  while (!(response))
  {
    Serial3.print("AT+ADDR\r\n");
    data = Serial3.readString();
    if (data == "OK\r\n")
      response++;
  }
  response = 0;
  while (!(response))
  {
    Serial3.print("AT+UART=115200,0,0\r\n");
    data = Serial3.readString();
    if (data == "OK\r\n")
      response++;
  }
  response = 0;
  while (!(response))
  {
    Serial3.print("AT+NAME=evive\r\n");
    data = Serial3.readString();
    if (data == "OK\r\n")
      response++;
  }
  response = 0;
  while (!(response))
  {
    Serial3.print("AT+PSWD=0000\r\n");
    data = Serial3.readString();
    if (data == "OK\r\n")
      response++;
  }
  response = 0;
  Serial3.print("AT+INIT\r\n");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

  // put your main code here, to run repeatedly:

}
