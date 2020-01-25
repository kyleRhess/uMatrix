 
 //#define DEBUG
#include "uMatrix.h"
#include "pinFunctions.h"
#include "Arduino.h"
#include <SPI.h>

//<<constructor>>
uMatrix::uMatrix() {}

//<<deconstructor>>
uMatrix::~uMatrix() {}

void uMatrix::initial(int latchPin, int clockPin, int dataPin, int OE)
{
	// State matrix
	_Bool stateMatrix[NUM_ROWS][NUM_COLS];

	// Left and right column bytes
	unsigned long rowWords[NUM_ROWS];

	// Track rows that have changed
	_Bool rowStateChange[NUM_ROWS];
	prevTime = 0;
	lastCount = charCount = 0;

	setOutputPin(latchPin);
	setOutputPin(clockPin);
	setOutputPin(dataPin);
	setOutputPin(OE);

	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
	_OE = OE;

	digWrite(OE, HIGH);
	PORTB &= ~_BV(PB0);

	// Initialize all elements to start off
	for (int i = 0; i < NUM_ROWS; i++)
	{
		rowWords[i] = 0xFFFFFFFF;
		rowStateChange[i] = 1;
		for (int j = 0; j < NUM_COLS; j++)
		{
			stateMatrix[i][j] = 1;
		}
	}

	// SET PWM FREQ TO 31kHz (9&10)
	TCCR1B = TCCR1B & B11111000 | B00000001;
	_delay_ms(200);
	setBrightness(0);
}

void uMatrix::refreshMatrix()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		//digWrite(_latchPin, LOW);
		PORTB &= ~(1 << 0); // low if low

		/*THIS IS SLOWER THAN NORMAL SHIFTOUT*/
		//sendByte(_dataPin, _clockPin, (rowWords[i] >> 8));
		//sendByte(_dataPin, _clockPin, rowWords[i]);
		//sendByte(_dataPin, _clockPin, rows[i]);

		/*REPLACE THIS WITH CUSTOM SHIFTOUT()*/
		//shiftOut(_dataPin, _clockPin, MSBFIRST, (rowWords[i] >> 8));
		//shiftOut(_dataPin, _clockPin, MSBFIRST, rowWords[i]);
		//shiftOut(_dataPin, _clockPin, MSBFIRST, rows[i]);

		/*SPI IS FAST. Need arduino library tho*/
		//SPI.transfer((rowWords[i]));
		SPI.transfer16(rowWords[i]);
		SPI.transfer(1 << i);

		//digWrite(_latchPin, HIGH);
		PORTB |= (1 << 0); // high if high

#ifdef DEBUG
		_delay_us(50000);
#endif
	}

	PORTB &= ~(1 << 0); // low if low
	SPI.transfer(0xffff);
	SPI.transfer(0xffff);
	SPI.transfer(1 << 7);
	PORTB |= (1 << 0); // high if high
}

//
// Sets the current pixel values in the row 'buffer'
// Takes some time so only run when needed (if rowStateChanged)
//
void uMatrix::updateMatrixRow(int row)
{
#if 0
	for (int i = 0; i < NUM_ROWS; i++)
	{
		if (rowStateChange[i])
		{
			rowWords[i] = 0x0000;
			for (int col = 0; col < NUM_COLS; col++)
			{
				if (stateMatrix[i][col] == 0)
				{
					// fill with 1's
					rowWords[i] = (rowWords[i] | (0x0001 << col));
				}
				else
				{
					// fill with 0's
					rowWords[i] = (rowWords[i] | (0x0000 << col));
				}
			}
			rowStateChange[i] = 0;
		}
	}
#endif
}

void uMatrix::setBrightness(int value)
{
	if (value > 0)
	{
		analogWrite(_OE, value);
	}
	else
	{
		digWrite(_OE, LOW); // Brightest
	}
}

//
// Sets the specified pixel state.
// Must be called before updateMatrixRow()
//
void uMatrix::setPixelState(int row, int column, int state)
{
	if (row < NUM_ROWS && column < NUM_COLS)
	{
		stateMatrix[row][column] = state;

		switch (state)
		{
		case 1:
			rowWords[row] = (rowWords[row] & ~(1 << column));
			break;
		case 0:
			rowWords[row] = (rowWords[row] | (1 << column));
			break;
		default:
			break;
		}
	}
}

//
// Sets the specified pixel state.
// Must be called before updateMatrixRow()
//
void uMatrix::setPixelState(int pix, _Bool state)
{
	if (pix >= 0)
	{
		int row = (pix / 16);
		int column = (pix % 16);
		setPixelState(row, column, state);
	}
}

//
// Returns current pixel state
//
_Bool uMatrix::getPixelState(int row, int column)
{
	if (row < NUM_ROWS && column < NUM_COLS)
	{
		return stateMatrix[row][column];
	}
}

//
// Set all pixels to off state
//
void uMatrix::clearAll()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			setPixelState(i, j, 0);
		}
	}
}

//
// Set all pixels to on state
//
void uMatrix::allOn()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			setPixelState(i, j, 1);
		}
	}
}

//
// Swap the states of two pixel locations (r1, c1, r2, c2)
//
void uMatrix::swapPixels(int r1, int c1, int r2, int c2)
{
	setPixelState(r2, c2, getPixelState(r1, c1));
	setPixelState(r1, c1, !getPixelState(r1, c1));
}

void uMatrix::drawRect(int h, int w)
{
	h = h - 1;
	w = w - 1;
	for (int i = 0; i <= h; i++)
	{
		if (i == 0)
		{
			for (int j = 1; j < w; j++)
			{
				setPixelState(0, j, 1);
			}
		}
		else if (i == h)
		{
			for (int j = 1; j < w; j++)
			{
				setPixelState(h, j, 1);
			}
		}
		setPixelState(i, 0, 1);
		setPixelState(i, w, 1);
	}
}

void uMatrix::offsetX(int dist)
{
	int count;
	if (dist > 0)
	{
		while (count < dist)
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				for (int j = NUM_COLS - 1; j >= 0; j--)
				{
					if (j != 0)
					{
						setPixelState(i, j, getPixelState(i, j - 1));
					}
					else
					{
						setPixelState(i, j, 0);
					}
				}
			}
			count++;
		}
	}
	else
	{
		while (count < abs(dist))
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				for (int j = 0; j < NUM_COLS; j++)
				{
					if (j != 15)
					{
						setPixelState(i, j, getPixelState(i, j + 1));
					}
					else
					{
						setPixelState(i, j, 0);
					}
				}
			}
			count++;
		}
	}
}

void uMatrix::offsetY(int dist)
{
	int count;
	if (dist > 0)
	{
		while (count < dist)
		{
			for (int i = NUM_ROWS - 1; i >= 0; i--)
			{
				for (int j = 0; j < NUM_COLS; j++)
				{
					if (i != 0)
					{
						setPixelState(i, j, getPixelState(i - 1, j));
					}
					else
					{
						setPixelState(i, j, 0);
					}
				}
			}
			count++;
		}
	}
	else
	{
		while (count < abs(dist))
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				for (int j = 0; j < NUM_COLS; j++)
				{
					if (i != 15)
					{
						setPixelState(i, j, getPixelState(i + 1, j));
					}
					else
					{
						setPixelState(i, j, 0);
					}
				}
			}
			count++;
		}
	}
}
