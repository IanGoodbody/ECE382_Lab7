/*
 * rangeFinder.c
 *
 *  Created on: Dec 4, 2014
 *      Author: C16Ian.Goodbody
 */

#include "rangeFinder.h"
#include <msp430.h>

void initRangeFinders()
{
	ADC10CTL0 |= ADC10SHT_3|ADC10ON|ADC10IE;
	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;

}

void readRight(int *bufferPtr)
{
	ADC10CTL1 &= ~INCH_15;
	ADC10CTL1 |= INCH_0;
	ADC10AE0 |= BIT0;
	ADC10CTL0 |= ENC|ADC10SC;
	__bis_SR_register(CPUOFF + GIE);
	rotateIn(bufferPtr, ADC10MEM);
}

void readLeft(int *bufferPtr)
{
	ADC10CTL1 &= ~INCH_15;
	ADC10CTL1 |= INCH_1;
	ADC10AE0 |= BIT1;
	ADC10CTL0 |= ENC|ADC10SC;
	__bis_SR_register(CPUOFF + GIE);
	rotateIn(bufferPtr, ADC10MEM);
}

void readForward(int *bufferPtr)
{
	ADC10CTL1 &= ~INCH_15;
	ADC10CTL1 |= INCH_2;
	ADC10AE0 |= BIT2;
	ADC10CTL0 |= ENC|ADC10SC;
	__bis_SR_register(CPUOFF + GIE);
	rotateIn(bufferPtr, ADC10MEM);
}

void fillBuffers(int *forwardBufferPtr, int *leftBufferPtr, int *rightBufferPtr)
{

}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

/*
 * rotateIn
 *
 * Moves all values down one index, dropes the value at index 0, then adds
 * val to the last index value
 */
void rotateIn(int *bufferPtr, int val)
{
	int i;
	for(i = BUFFER_LN-1; i > 0; i--) // Will run BUFFER_LN-1 times
	{
		*bufferPtr = *(bufferPtr+1);
		bufferPtr++;
	}
	*bufferPtr = val;
}

int mean(int *bufferPtr)
{
	int i;
	int sum = *(bufferPtr++);
	for(i = BUFFER_LN-1; i > 0; i--)
	{
		sum += *(bufferPtr++);
	}
	return sum >> 3;
}

int median(int *bufferPtr)
{
	int sortBuffer[BUFFER_LN];

	// Copy over the data buffer
	int *sortBufferPtr = sortBuffer;
	int i, j;
	for(i = BUFFER_LN; i > 0; i--)
	{
		*(sortBufferPtr++) = *(bufferPtr++);
	}

	// Bubble sort through half the sort array
	for(j = BUFFER_LN; j > (BUFFER_LN>>1)-1; j--)
	{
		sortBufferPtr = sortBuffer;
		for(i = 0; i < j-1; i++)
		{
			if(*sortBufferPtr > *(sortBufferPtr+1))
			{
				*sortBufferPtr ^= *(sortBufferPtr+1);
				*(sortBufferPtr+1) ^= *sortBufferPtr;
				*sortBufferPtr ^= *(sortBufferPtr+1);
			}
			sortBufferPtr++;
		}
	}
	return (sortBuffer[BUFFER_LN>>1]+sortBuffer[(BUFFER_LN>>1)-1])>>1;
}
