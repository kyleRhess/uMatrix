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

	void 	initial(int latchPin, int clockPin, int dataPin, int OE);
	void 	refreshMatrix();
	void 	updateMatrixRow(int row);
	void	setBrightness(int value);
	void 	setPixelState(int row, int column, int state);
	void 	setPixelState(int pix, _Bool state);
	_Bool 	getPixelState(int row, int column);
	void 	clearAll();
	void 	allOn();
	void 	swapPixels(int r1, int c1, int r2, int c2);
	void 	drawChar(char ch);
	void 	drawRect(int height, int width);
	void 	offsetX(int dist);
	void 	offsetY(int dist);
	
private:
	//latchPin connected to ST_CP of 74HC595
	//clockPin connected to SH_CP of 74HC595
	//dataPin connected to DS of 74HC595
	//Output enable pin
	int _latchPin, _clockPin, _dataPin, _OE;

	_Bool stateMatrix[NUM_COLS][NUM_COLS];	//State matrix
	unsigned short rowWords[NUM_ROWS];		//Left and right column pixel bytes
	_Bool rowStateChange[NUM_ROWS];			//Track rows that have changed
	long count, prevTime, currentTime;
	long lastCount, charCount;

};

#endif // !UMATRIX_H

