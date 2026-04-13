/*
 * zizhuo_macropad.c
 *
 * Created: 12/4/2026 12:28:17 am
 * Author : Yu Heng
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "keys.h"

int main(void)
{
	DDRD = 0xff;
	PORTD = 0x00;
	
	//blinky();
	
	keys_init();
	
	uint8_t key_arr[6];
	
	while(1) {
		read_key(key_arr);
		_delay_ms(1000);
	}
}