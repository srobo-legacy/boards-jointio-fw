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

#include "in.h"
#include <io.h>

uint16_t in_buffer[8];

void in_init(void) {
	/* LEDs */
	P1OUT = 0x00;
	P1DIR = 0xFF;

	/* Inputs */
	ADC10AE0 = 0xFF;

	/* Setup ADC control registers */
	ADC10CTL0 = SREF_AVCC_AVSS /* Use VCC/VSS as the +ve/-ve reference */
	          | ADC10SHT_DIV64 /* 64 clock cycle sample and hold time */
	          | MSC            /* Enable multiple sample and conversion */
	          | ADC10ON;       /* Enable ADC10 module */

	ADC10CTL1 = ADC10DIV_7     /* Divide clock by 7 */
	          | INCH_7         /* Convert from A7 down to A0 */
	          | CONSEQ_3;     /* Continuously convert all channels */

	/* Setup ADC DTC (Data Transfer Controller) module */
	ADC10DTC0 = ADC10CT;       /* Continuously trasnfer data */
	ADC10DTC1 = 8;             /* Block is 8 samples long */
	ADC10SA = (uint16_t)&in_buffer;      /* Set address to write samples to */

	ADC10CTL0 |= ENC | ADC10SC; /* Enable/Start conversion */
}

void in_set(uint8_t a) {
	P1OUT = a;
}

uint8_t in_get_a(void) {
	return P1OUT;
}

uint8_t in_get_d(void) {
	return P1OUT;
}
