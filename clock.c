#include <clock.h>

/*
 * The clock is sumulated by a function that calls every elements that needs a clock input a regular intervals
 *
 */

how to layout chips in memory

clock calls updateState[state of chip, newState] and saves the new state

struct flipflopState {
	int clock;
	int in;
	int out;
}

struct flipflopState flipflopStates[16];

int i;
for(i=0; i<sizeof(flipflopStates); i++) {
	updateFliplop(&flipflipStates[i]);
}
