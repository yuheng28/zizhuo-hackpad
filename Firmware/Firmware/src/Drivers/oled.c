/*
 * oled.c
 *
 * Created: 13/4/2026 11:28:37 pm
 *  Author: Yu Heng
 */ 

#include <avr/io.h>
#include <stddef.h>
#include "oled.h"

void oled_init() {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);

	i2c_send(0x00); // command mode

	i2c_send(0xAE); // display OFF
	i2c_send(0xD5); i2c_send(0x80);
	i2c_send(0xA8); i2c_send(0x3F);
	i2c_send(0xD3); i2c_send(0x00);
	i2c_send(0x40);
	i2c_send(0x8D); i2c_send(0x14); // charge pump ON
	i2c_send(0x20); i2c_send(0x00); // horizontal addressing mode
	i2c_send(0xA1);
	i2c_send(0xC8);
	i2c_send(0xDA); i2c_send(0x12);
	i2c_send(0x81); i2c_send(0x7F);
	i2c_send(0xA4);
	i2c_send(0xA6);
	i2c_send(0xAF); // display ON

	i2c_send_stop();
}

void oled_inverse_screen() {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x00); // Co = 0, D/C# = 0 (command)
	i2c_send(0xA7); // entire screen on
	i2c_send_stop();
}

void oled_turn_on() {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x00); // Co = 0, D/C# = 0 (command)
	i2c_send(0xA5); // entire screen on
	i2c_send_stop();
}

void oled_turn_off() {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x00); // Co = 0, D/C# = 0 (command)
	i2c_send(0xA4); // disable entire screen on
	i2c_send_stop();
}

void oled_set_addressing() {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x00);

	i2c_send(0x21); // column address
	i2c_send(0x00); // start column
	i2c_send(0x7F); // end column

	i2c_send(0x22); // page address
	i2c_send(0x00); // start page
	i2c_send(0x07); // end page (32px display)

	i2c_send_stop();
}

void oled_update_ram(uint8_t *arr) {
	uint16_t i = 0;
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x40); // Co = 0, D/C# = 1 (data)
	
	i = 0;
	
	while (i < CACHE_SIZE) {
		i2c_send(arr[i++]);
	}
	
	i2c_send_stop();
}