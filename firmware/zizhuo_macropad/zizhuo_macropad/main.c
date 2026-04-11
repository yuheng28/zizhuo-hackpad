/*
 * zizhuo_macropad.c
 *
 * Created: 12/4/2026 12:28:17 am
 * Author : OSdoge
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void blinky(void) {
	DDRD = 0xff;
	PORTD = 0x00;
	
	/* Replace with your application code */
	while (1)
	{
		PORTD ^= 0xff;
		_delay_ms(1000);
	}
}

int main(void)
{
	blinky();
}

