/*
 * rangeFinder.h
 *
 *  Created on: Dec 4, 2014
 *      Author: C16Ian.Goodbody
 */

#ifndef RANGEFINDER_H_
#define RANGEFINDER_H_

#define BUFFER_LN 8
#define FAR_THRESHOLD 34
#define CLOSE_THRESHOLD 17

void readRight(int *bufferPtr);
void readLeft(int *bufferPtr);
void readFront(int *bufferPtr);

void rotateIn(int *bufferPtr, int val);
int mean(int *bufferPtr);
int median(int *bufferPtr);

void initRangeFinders();
void fillBuffers(int *forwardBufferPtr, int *leftBufferPtr, int *rightBufferPtr);

#endif /* RANGEFINDER_H_ */
