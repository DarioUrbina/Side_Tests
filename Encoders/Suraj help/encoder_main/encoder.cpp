#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "encoder.h"

#define pinA PD2
#define pinB PD3


volatile unsigned char new_state, old_state;
volatile long *encPulses;
volatile long count = 0;
volatile unsigned char a, b;

volatile unsigned char changed = 0;  // Flag for state change



void encoder_init() {
	DDRD  &= ~((1 << PD2) | (1 << PD3));
	PORTD |=  ((1 << PD2) | (1 << PD3)); //rotary encoder pull-up resistors
	initialState();
	
	//enable interrupts
	PCICR |= (1 << PCIE2);
	PCMSK0 |= ((1 << PCINT18) | (1 << PCINT19));
	sei();	
}

void initialState(void) {
    // Read the A and B inputs to determine the intial state   
	char output = (PIND & ((1 << PD2) | (1 << PD3)) );
	a = (output & (1 << PD2));
	b = (output & (1 << PD3));

    if (!b && !a)
		old_state = 0;
    else if (!b && a)
		old_state = 1;
    else if (b && !a)
		old_state = 2;
    else
		old_state = 3;

    new_state = old_state;
}

long getPulses() {
	return count;
}

unsigned isChanged() {
	if (changed == 1)
	{
		changed = 0;
		return 1;
	}
	return 0;
}

ISR(PCINT2_vect) {
	// Read the input bits and determine A and B
	char output = (PIND & ((1 << PD2) | (1 << PD3)) );
	a = (output & (1 << PD2));
	b = (output & (1 << PD3));

	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
	if (old_state == 0) {
		// Handle A and B inputs for state 0
		if(!b && a) {
			new_state = 1;
			count++;
		}
		else if(b && !a) {
			new_state = 2;
			count--;
		}

	}
	else if (old_state == 1) {
		// Handle A and B inputs for state 1
		if(a && b) {
			new_state = 3;
			count++;
		}
		else if(!a && !b) {
			new_state = 0;
			count--;
		}

	}
	else if (old_state == 2) {
		// Handle A and B inputs for state 2
		if(a && b) {
			new_state = 3;
			count--;
		}
		else if(!a && !b) {
			new_state = 0;
			count++;
		}
	}
	else {   // old_state = 3
		// Handle A and B inputs for state 3
		if(!b && a) {
			new_state = 1;
			count--;
		}
		else if(b && !a) {
			new_state = 2;
			count++;
		}
	}

	//If state changed and count not out of bounds, update the
	//value of old_state, and set a flag that the state has changed.
	if (new_state != old_state) {
		changed = 1;
	}
	old_state = new_state;
}
