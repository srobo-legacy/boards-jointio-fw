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

void in_init(void) {
	/* LEDs */
	P1OUT = 0x00;
	P1DIR = 0xFF;

	/* Inputs */
	P2DIR &= ~0x1F; /* P2.0 to P2.4 */
	P3DIR &= ~0xC1; /* P3.0, P3.6 and P3.7 */
}

uint8_t in_get_a(void) {
	return P1OUT;
}

uint8_t in_get_d(void) {
	return P1OUT;
}
