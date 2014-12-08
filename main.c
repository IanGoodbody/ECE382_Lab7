#include <msp430.h> 
#include "rangeFinder.h"
#include "testMethods.h"

/*
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    testRangeFinders(); // This code will run the requied functionality.

    while(1);
}
