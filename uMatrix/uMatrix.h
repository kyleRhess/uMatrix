#ifndef UMATRIX_H
#define UMATRIX_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
#endif

#define NUM_ROWS	8
#define NUM_COLS	16
#define WORDSIZE	24	//Bits

class uMatrix {
public:
	uMatrix();
	~uMatrix();

	void initial(int latchPin, int clockPin, int dataPin, int OE);
	void refreshMatrix(int mDelay);
	void updateMatrixRow(int row);
	void setPixelState(int row, int column, _Bool state);
	void setPixelState(int pix, _Bool state);
	_Bool getPixelState(int row, int column);
	void clearAll();
	void allOn();
	void swapPixels(int r1, int c1, int r2, int c2);
	void drawChar(char ch);
	void drawRect(int height, int width);
	void offsetX(int dist);
	void offsetY(int dist);
	

private:
	//latchPin connected to ST_CP of 74HC595
	//clockPin connected to SH_CP of 74HC595
	//dataPin connected to DS of 74HC595
	//Output enable pin
	byte _latchPin, _clockPin, _dataPin, _OE;

	unsigned char rows[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
	_Bool stateMatrix[NUM_COLS][NUM_COLS];	//State matrix
	unsigned short rowWords[NUM_ROWS];		//Left and right column bytes
	_Bool rowStateChange[NUM_ROWS];			//Track rows that have changed
	long count, prevTime;

};

#endif // !UMATRIX_H

