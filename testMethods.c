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
	DCOCTL = CALDCO_8MHZ;

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

void testRangeFinders()
{
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	initRangeFinders();

	P1DIR |= LEFT_LED|RIGHT_LED;


	int fBuffer[BUFFER_LN];
	int lBuffer[BUFFER_LN];
	int rBuffer[BUFFER_LN];
	int mf;
	int ml;
	int mr;

	fillBuffers(fBuffer, lBuffer, rBuffer);

	while(1)
	{
		readFront(fBuffer);
		readLeft(lBuffer);
		readRight(rBuffer);
		mf = median(fBuffer);
		ml = median(lBuffer);
		mr = median(rBuffer);

		if(mf > 0x01F0)
		{
			P1OUT |= (RIGHT_LED|LEFT_LED);
		}
		else if(ml > 0x0220)
		{

			P1OUT &= ~RIGHT_LED;
			P1OUT |= LEFT_LED;
		}
		else if(mr > 0x0220)
		{
			P1OUT &= ~LEFT_LED;
			P1OUT |= RIGHT_LED;
		}
		else
		{
			P1OUT &= ~(LEFT_LED|RIGHT_LED);
		}
	}

}

void testBuffers(void)
{
	initRangeFinders();

	int fBuffer[BUFFER_LN];
	int lBuffer[BUFFER_LN];
	int rBuffer[BUFFER_LN];

	volatile int fMean;
	volatile int fMed;
	volatile int rMean;
	volatile int rMed;
	volatile int lMean;
	volatile int lMed;

	while(1)
	{
		fillBuffers(fBuffer, lBuffer, rBuffer);
		fMean = mean(fBuffer);
		fMed = median(fBuffer);
		lMean = mean(lBuffer);
		lMed = median(lBuffer);
		rMean = mean(rBuffer);
		rMed = median(rBuffer);
	}
}
