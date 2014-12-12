#include <msp430.h> 
#include "rangeFinder.h"
#include "testMethods.h"

/*
 * main.c
 * This code will implement the functionality for the lab, turning LEDs on and off according to sensors
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    testRangeFinders(); // This code will run the requied functionality.

    while(1);
}
