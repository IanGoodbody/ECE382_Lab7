/*
 * testMethods.c
 *
 *  Created on: Dec 4, 2014
 *      Author: C16Ian.Goodbody
 */

#include <MSP430.h>
#include "rangeFinder.h"
#include "testMethods.h"

void testMath()
{
    int i;
    volatile int testArray[BUFFER_LN];
    for(i = 8; i > 0; i--)
    {
    	rotateIn(testArray, i);
    }
    volatile int average = mean(testArray);
    volatile int middle = median(testArray);

    volatile int testArray2[BUFFER_LN] = {16, 6, 12, 10, 4, 14, 8, 2};
    average = mean(testArray2);
    middle = median(testArray2);
}

void testLEDsTimer()
{
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;;

	P1DIR |= LEFT_LED|RIGHT_LED;
	P1OUT |= LEFT_LED;
	P1OUT &= ~RIGHT_LED;

	TACTL &= ~(MC_3);
	TACTL &= ~TAIFG;
	TACTL |= TASSEL_2|ID_3|TAIE;
	TACCR0 = 0xFFFF;
	TAR = 0x0000;

	//IFG1 = 1;

	TACTL |= MC_1;

}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timerA0Overflow(void)
{
	P1OUT ^= (LEFT_LED|RIGHT_LED);
	TA0CTL &= ~TAIFG;
}
