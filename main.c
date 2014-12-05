#include <msp430.h> 
#include "rangeFinder.h"
#include "testMethods.h"

/*
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    IFG1 = 0;

    testLEDsTimer();
    _enable_interrupt();

    while(1);
}
