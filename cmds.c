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

#include <string.h>
#include "cmds.h"
#include "out.h"
#include "in.h"

static uint8_t sric_output_set(const sric_if_t *iface);
static uint8_t sric_output_get(const sric_if_t *iface);
static uint8_t sric_input_a(const sric_if_t *iface);
static uint8_t sric_input_d(const sric_if_t *iface);

const sric_cmd_t sric_commands[] = {
	{sric_output_set},
	{sric_output_get},
	{sric_input_a},
	{sric_input_d}
};

const uint8_t sric_cmd_num = sizeof(sric_commands) / sizeof(const sric_cmd_t);

static uint8_t sric_output_set(const sric_if_t *iface) {
	out_set(iface->rxbuf[SRIC_DATA+1]);
	return 0;
}

static uint8_t sric_output_get(const sric_if_t *iface) {
	iface->txbuf[0] = out_get();
	return 1;
}

static uint8_t sric_input_a(const sric_if_t *iface) {
	memcpy(iface->txbuf, in_buffer, 16);
	return 16;
}

static uint8_t sric_input_d(const sric_if_t *iface) {
	iface->txbuf[0] = in_get_d();
	return 1;
}
