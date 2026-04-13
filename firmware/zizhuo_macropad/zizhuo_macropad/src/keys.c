/*
 * keys.c
 *
 * Created: 12/4/2026 9:34:35 pm
 *  Author: Yu Heng
 */ 

#include <avr/io.h>
#include "keys.h"

uint8_t key_map[6] = {KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F};

void keys_init(void) {
	/* All the keys are on Port B
		PB1 PB2 PB3
		PB4 PB5 PB6
	*/
	
	DDRB = 0x00; // set to input
	PORTB = 0xFF; // set internal pullups
}

void blink(void) {
	PORTD ^= 0xff;
}

void read_key(uint8_t *key_arr) {
	// when unpressed, we expect high
	
	// for testing
	//if (!(PINB & (1 << PB1))) {
		//// if Key 1 is low
		//blink();
	//}
	
	uint8_t pins = PINB; // to prevent reading 6 times
	
	for (uint8_t i = 0; i < 6; i++) {
		key_arr[i] = (!(pins & (1 << (i + 1)))) ? key_map[i] : 0;
	}
}