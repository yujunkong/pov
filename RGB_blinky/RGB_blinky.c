/*
 * RGB_blinky.c
 *
 *  Created on: 2017. 12. 13.
 *      Author: JS
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_apa102.h"

struct cRGB led[50];

int main(void) {

	while (1) {
		for (int i = 0; i < 50; i++) {
			led[i].r = 0;
			led[i].g = 255;
			led[i].b = 0;    // Write red to array
			apa102_setleds(led, 50);
			// wait for 500ms.
			//_delay_ms(10);
		}

	}
}
