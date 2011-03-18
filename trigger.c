/*   Copyright (C) 2010 Richard Barlow

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "trigger.h"
#include "in.h"
#include <io.h>

static volatile uint8_t trigger_enabled;
static volatile uint16_t trigger_threshold[8];
static volatile trigger_op_t trigger_operation[8];

void trigger_init(void) {
}

void trigger_set_en(uint8_t index, bool en) {
	if (index < 8) {
		if (en)
			trigger_enabled |= 1<<index;
		else
			trigger_enabled &= ~(1<<index);
	}
}

bool trigger_get_en(uint8_t index) {
	if (index < 8)
		return trigger_enabled & index;
	else
		return 0;
}

void trigger_set_thresh(uint8_t index, uint16_t thresh) {
	if (index < 8)
		trigger_threshold[index] = thresh;
}
uint16_t trigger_get_thresh(uint8_t index) {
	if (index < 8)
		return trigger_threshold[index];
	else
		/* TODO: should return error value */
		return 0;
}

void trigger_set_op(uint8_t index, trigger_op_t op) {
	if (index < 8)
		trigger_operation[index] = op;
}
trigger_op_t trigger_get_op(uint8_t index) {
	if (index < 8)
		return trigger_operation[index];
	else
		/* TODO: should return error value */
		return 0;
}

uint8_t trigger_check() {
	uint8_t flags = 0;
	int i;
	for (i = 0; i < 8; i++) {
		if (trigger_enabled & i) {
			switch (trigger_operation[i]) {
			case TRIG_OP_LESS:
				if (in_buffer[i] < trigger_threshold[i])
					flags |= 1<<i;
				break;
			case TRIG_OP_GREATER:
				if (in_buffer[i] > trigger_threshold[i])
					flags |= 1<<i;
				break;
			}
		}
	}

	return flags;
}
