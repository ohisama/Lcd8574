#include "Lcd8574.h"

Lcd8574::Lcd8574(void)
{
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
}
void Lcd8574::begin(uint8_t cols, uint8_t lines, uint8_t dotsize)
{
	_i2c.begin();
	if (lines > 1)
	{
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;
	_currline = 0;
	if ((dotsize != 0) && (lines == 1))
	{
		_displayfunction |= LCD_5x10DOTS;
	}
	_i2c.send(0x03);
	delayMicroseconds(50);
	_i2c.send(0x03);
	delayMicroseconds(50);
	_i2c.send(0x03);
	delayMicroseconds(15);
	_i2c.send(0x02);
	command(LCD_FUNCTIONSET | _displayfunction);
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	clear();
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}
void Lcd8574::send(uint8_t value, uint8_t mode)
{
	if (mode)
	{
		_i2c.echo(value);
	}
	else
	{
		_i2c.set(value);
	}
}
inline void Lcd8574::command(uint8_t value)
{
	send(value, LOW);
}
inline size_t Lcd8574::write(uint8_t value)
{
	send(value, HIGH);
	return 1;
}
void Lcd8574::clear()
{
	command(LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}
void Lcd8574::home()
{
	command(LCD_RETURNHOME);
	delayMicroseconds(2000);
}
void Lcd8574::setCursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = {
		0x00,
		0x40,
		0x14,
		0x54
	};
	if (row > _numlines)
	{
		row = _numlines - 1;
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}
void Lcd8574::noDisplay()
{
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::display()
{
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::noCursor()
{
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::cursor()
{
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::noBlink()
{
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::blink()
{
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void Lcd8574::scrollDisplayLeft(void)
{
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void Lcd8574::scrollDisplayRight(void)
{
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}
void Lcd8574::leftToRight(void)
{
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}
void Lcd8574::rightToLeft(void)
{
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}
void Lcd8574::autoscroll(void)
{
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}
void Lcd8574::noAutoscroll(void)
{
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}
void Lcd8574::createChar(uint8_t location, uint8_t charmap[])
{
	location &= 0x7;
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i = 0; i < 8; i++)
	{
		write(charmap[i]);
	}
}
