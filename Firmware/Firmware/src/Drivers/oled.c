/*
 * oled.c
 *
 * Created: 13/4/2026 11:28:37 pm
 *  Author: Yu Heng
 */ 

#include <avr/io.h>
#include <stddef.h>
#include <avr/delay.h>
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

void oled_set_addressing(uint8_t start_col, uint8_t start_page) {
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x00);

	i2c_send(0x21); // column address
	i2c_send(start_col); // start column
	i2c_send(0x7F); // end column

	i2c_send(0x22); // page address
	i2c_send(start_page); // start page
	i2c_send(0x07); // end page (64px display)

	i2c_send_stop();
}

static uint16_t oled_index = 0;
static uint8_t *oled_buf = NULL;
volatile uint8_t oled_busy = 0;

void oled_start_update(uint8_t *arr) {
	if (oled_busy) return;

	oled_buf = arr;
	oled_index = 0;
	oled_busy = 1;
	
	oled_set_addressing(0, 0);
}

void oled_update_step() {
	if (!oled_busy) return;

	// First call ? send header
	//if (oled_index == 0) {
		//
	//}
	
	// Send a small chunk per call
	uint8_t chunk = 128;  // ?? should be multiple of 8 and factor of 64

	//oled_set_addressing(oled_index % 128, (oled_index / 128)); // columns are 128 pixels, each page is 8 rows. / takes floor for integers

	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x40); // data mode

	for (uint8_t i = 0; i < chunk && oled_index < CACHE_SIZE; i++) {
		i2c_send(oled_buf[oled_index++]);
		USB_USBTask();
	}
	i2c_send_stop();

	// Done
	if (oled_index >= CACHE_SIZE) {
		oled_busy = 0;
	}
}

void oled_update_ram(uint8_t *arr) {
	oled_set_addressing(0, 0);
	i2c_send_start();
	i2c_enter_MT_mode(OLED_ADDR);
	i2c_send(0x40); // Co = 0, D/C# = 1 (data)
	
	uint16_t i = 0;
	while (i < CACHE_SIZE) {
		i2c_send(arr[i++]);
	}
	
	i2c_send_stop();
}