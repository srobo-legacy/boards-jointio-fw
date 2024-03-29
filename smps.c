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

#include "smps.h"
#include <io.h>

void smps_init(void) {
	P2SEL &= ~(1<<7);
	P2OUT |= 1<<7;
	P2DIR |= 1<<7;
}

void smps_en(void) {
	P2OUT &= ~(1<<7);
}

void smps_dis(void) {
	P2OUT |= 1<<7;
}
