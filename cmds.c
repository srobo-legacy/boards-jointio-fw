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
#include "smps.h"
#include "trigger.h"
#include "flash430/sric-flash.h"

static uint8_t sric_output_set(const sric_if_t *iface);
static uint8_t sric_output_get(const sric_if_t *iface);
static uint8_t sric_input_a(const sric_if_t *iface);
static uint8_t sric_input_d(const sric_if_t *iface);
static uint8_t sric_smps(const sric_if_t *iface);
static uint8_t sric_trigger_set_en(const sric_if_t *iface);
static uint8_t sric_trigger_set_thresh(const sric_if_t *iface);
static uint8_t sric_trigger_set_op(const sric_if_t *iface);
static uint8_t sric_trigger_get_en(const sric_if_t *iface);
static uint8_t sric_trigger_get_thresh(const sric_if_t *iface);
static uint8_t sric_trigger_get_op(const sric_if_t *iface);

const sric_cmd_t sric_commands[] = {
	{sric_output_set},
	{sric_output_get},
	{sric_input_a},
	{sric_input_d},
	{sric_smps},
	{sric_flashr_fw_ver},
	{sric_flashw_fw_chunk},
	{sric_flashr_fw_next},
	{sric_flashr_crc},
	{sric_flashw_confirm},
	{sric_trigger_set_en},
	{sric_trigger_get_en},
	{sric_trigger_set_thresh},
	{sric_trigger_get_thresh},
	{sric_trigger_set_op},
	{sric_trigger_get_op},
};

const uint8_t sric_cmd_num = sizeof(sric_commands) / sizeof(const sric_cmd_t);

static uint8_t sric_output_set(const sric_if_t *iface) {
	out_set(iface->rxbuf[SRIC_DATA+1]);
	return 0;
}

static uint8_t sric_output_get(const sric_if_t *iface) {
	iface->txbuf[SRIC_DATA+0] = out_get();
	return 1;
}

static uint8_t sric_input_a(const sric_if_t *iface) {
	uint8_t i;

	for( i=0; i<8; i++ ) {
		iface->txbuf[SRIC_DATA + i*2] = in_buffer[i] >> 8;
		iface->txbuf[SRIC_DATA + i*2 + 1] = in_buffer[i] & 0xff;
	}
	return 16;
}

static uint8_t sric_input_d(const sric_if_t *iface) {
	iface->txbuf[0+SRIC_DATA] = in_get_d();
	return 1;
}

static uint8_t sric_smps(const sric_if_t *iface) {
	if (iface->rxbuf[SRIC_DATA+1])
		smps_en();
	else
		smps_dis();
	return 0;
}

static uint8_t sric_trigger_set_en(const sric_if_t *iface) {
	uint8_t *data = iface->rxbuf + SRIC_DATA + 1;
	trigger_set_en(data[0], data[1]);
	return 0;
}

static uint8_t sric_trigger_set_thresh(const sric_if_t *iface) {
	uint8_t *data = iface->rxbuf + SRIC_DATA + 1;
	trigger_set_thresh(data[0], data[1] | (data[2] << 8));
	return 0;
}

static uint8_t sric_trigger_set_op(const sric_if_t *iface) {
	uint8_t *data = iface->rxbuf + SRIC_DATA + 1;
	trigger_set_op(data[0], data[1]);
	return 0;
}

static uint8_t sric_trigger_get_en(const sric_if_t *iface) {
	iface->txbuf[SRIC_DATA] = trigger_get_en(iface->rxbuf[SRIC_DATA+1]);
	return 1;
}
static uint8_t sric_trigger_get_thresh(const sric_if_t *iface) {
	uint16_t thresh = trigger_get_thresh(iface->rxbuf[SRIC_DATA+1]);
	iface->txbuf[SRIC_DATA] = thresh & 0xff;
	iface->txbuf[SRIC_DATA+1] = (thresh >> 8) & 0xff;
	return 2;
}
static uint8_t sric_trigger_get_op(const sric_if_t *iface) {
	iface->txbuf[SRIC_DATA] = trigger_get_op(iface->rxbuf[SRIC_DATA+1]);
	return 1;
}
