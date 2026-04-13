/*
 * keys.h
 *
 * Created: 12/4/2026 9:34:28 pm
 *  Author: Yu Heng
 */ 


#ifndef KEYS_H_
#define KEYS_H_

#include "usb_hid_keys.h"

extern uint8_t key_map[6];

void keys_init(void);
void read_key(uint8_t *key_arr);

#endif /* KEYS_H_ */