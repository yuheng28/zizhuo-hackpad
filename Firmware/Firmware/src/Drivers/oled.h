/*
 * oled.h
 *
 * Created: 13/4/2026 11:28:45 pm
 *  Author: Yu Heng
 */ 


#ifndef OLED_H_
#define OLED_H_

#include "i2c.h"

#define OLED_ADDR 0x3C
#define CACHE_SIZE (128 * 64) / 8 // since 128 x 64 screen

extern uint8_t frame_one[CACHE_SIZE];
extern uint8_t frame_two[CACHE_SIZE];

void oled_init();
void oled_inverse_screen();
void oled_turn_on();
void oled_turn_off();
void oled_set_addressing();
void oled_update_ram(uint8_t *arr);

#endif /* OLED_H_ */