#ifndef __IN_H
#define __IN_H

#include <stdint.h>

extern uint16_t in_buffer[8];

void in_init(void);

void in_set(uint8_t);
uint8_t in_get_d(void);

#endif /* __IN_H */
