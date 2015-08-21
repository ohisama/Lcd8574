#include <Arduino.h>

class PCF8574 
{
public:
	void begin(void);
	void write(uint8_t d);
	void send(uint8_t d);
	void set(uint8_t d);  //command
	void echo(uint8_t d); //data
private:
};
#define PCF8574_ADDRESS 	0x27
