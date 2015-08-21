#include <Wire.h> 
#include <Lcd8574.h>

Lcd8574 lcd;

void setup()
{
	pinMode(13, OUTPUT);
	lcd = Lcd8574();
	lcd.begin(16, 2);
	lcd.print("hello, world!");
}
void loop()
{
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
	delay(1000);
}
