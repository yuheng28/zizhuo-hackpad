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

void oled_multiwrite(uint8_t ctrl, uint8_t *data, size_t size);

#endif /* OLED_H_ */