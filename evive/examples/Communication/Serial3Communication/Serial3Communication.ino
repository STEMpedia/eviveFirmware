/*
	This example is used to communicate with peripherals connected to Serial3 Port.
	Messages/Data read from Seripa Port 3 will be sent to Serial Port 0 (connected to USB) and vice-versa.
	
	Just simply change BAUD rate to your desired and open Serial Monitor in Arduino IDE
	
	Note: Make sure you have selected Both NL and CR at bottom of Serial monitor with proper baud
	
	Made by Nihar Shah
	On 12 October 2017.
*/

void setup() {
  Serial.begin(250000);							// Start Serial 0 (USB) at BAUD rate 250000
  Serial3.begin(115200);						// Start Serial 3 at BAUD here as per the module
  delay(50);
  Serial3.print("AT\r\n");    			// AT to check whether device is connected or not? Typically Replies with OK
}

void loop() {

  while (Serial.available())				//Checks wether any data is recieved on Serial (USB) (Serial Port 0)
  {
    Serial3.write(Serial.read());		//Reads the data from Serial Port 0 and send/write it to Serial Port 3
  }
	
  while (Serial3.available())				//Checks wether any data is recieved on Serial Port 3
  {
    Serial.write(Serial3.read());		//Reads the data from Serial Port 3 and send/write it to Serial Port 0
  }
  delay(100);
}