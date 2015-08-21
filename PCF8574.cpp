#include <Wire.h>
#include "PCF8574.h"

void PCF8574::begin(void)
{
	Wire.begin();
}
void PCF8574::write(uint8_t d)
{
	Wire.beginTransmission(PCF8574_ADDRESS);
	Wire.write(d);
	Wire.endTransmission();
}
void PCF8574::send(uint8_t d)
{
	uint8_t s;
	Wire.beginTransmission(PCF8574_ADDRESS);
	Wire.write(d);
	s = d | 0x04;
	Wire.write(s);
	delayMicroseconds(1);
	s = d & 0xfb;
	Wire.write(s);
	delayMicroseconds(1);
	Wire.endTransmission();
}
void PCF8574::set(uint8_t d)
{
	uint8_t s;
	uint8_t f1 = d & 0xf0;
	uint8_t f2 = d << 4;
	Wire.beginTransmission(PCF8574_ADDRESS);
	s = f1;
	Wire.write(s);
	s = f1 | 0x04;
	Wire.write(s);
	delayMicroseconds(1);
	s = f1 & 0xfb;
	Wire.write(s);
	Wire.endTransmission();
	Wire.beginTransmission(PCF8574_ADDRESS);
	s = f2;
	Wire.write(s);
	s = f2 | 0x04;
	Wire.write(s);
	delayMicroseconds(1);
	s = f2 & 0xfb;
	Wire.write(s);
	Wire.endTransmission();
}
void PCF8574::echo(uint8_t d)
{
	uint8_t s;
	uint8_t f1 = d & 0xf0;
	uint8_t f2 = d << 4;
	Wire.beginTransmission(PCF8574_ADDRESS);
	s = f1;
	Wire.write(s);
	s = f1 | 0x05;
	Wire.write(s);
	delayMicroseconds(1);
	s = f1 & 0xfa;
	Wire.write(s);
	Wire.endTransmission();
	Wire.beginTransmission(PCF8574_ADDRESS);
	s = f2;
	Wire.write(s);
	s = f2 | 0x05;
	Wire.write(s);
	delayMicroseconds(1);
	s = f2 & 0xfa | 0x08;
	Wire.write(s);
	Wire.endTransmission();
}
