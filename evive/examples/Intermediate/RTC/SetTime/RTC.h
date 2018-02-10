#define PCF8563address 0x51
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte bcdToDec(byte value)
{
  return ((value / 16) * 10 + value % 16);
}

byte decToBcd(byte value) {
  return (value / 10 * 16 + value % 10);
}
String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
void setPCF8563()
// this sets the time and date to the PCF8563
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.write(decToBcd(second));           //second
  Wire.write(decToBcd(minute));           //minute
  Wire.write(decToBcd(hour));             //hour
  Wire.write(decToBcd(dayOfMonth));       //date
  Wire.write(decToBcd(dayOfWeek));        //day of week see_the_above array
  Wire.write(decToBcd(month));            //month
  Wire.write(decToBcd(year));             //year
  Wire.endTransmission();
}

void readPCF8563()
// this gets the time and date from the PCF8563
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(PCF8563address, 7);
  second     = bcdToDec(Wire.read() & B01111111); // remove VL error bit
  minute     = bcdToDec(Wire.read() & B01111111); // remove unwanted bits from MSB
  hour       = bcdToDec(Wire.read() & B00111111);
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek  = bcdToDec(Wire.read() & B00000111);
  month      = bcdToDec(Wire.read() & B00011111);  // remove century bit, 1999 is over
  year       = bcdToDec(Wire.read());
}

