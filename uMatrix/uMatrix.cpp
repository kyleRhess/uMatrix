//#define DEBUG

#include "Arduino.h"
#include "uMatrix.h"

//<<constructor>>
uMatrix::uMatrix() {}

//<<deconstructor>>
uMatrix::~uMatrix() {}

void uMatrix::initial(int latchPin, int clockPin, int dataPin, int OE) 
{
	_Bool stateMatrix[NUM_ROWS][NUM_COLS];	//State matrix
	unsigned short rowWords[NUM_ROWS];		//Left and right column bytes
	_Bool rowStateChange[NUM_ROWS];			//Track rows that have changed
	prevTime = 0;

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(OE, OUTPUT);

	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
	_OE = OE;

	digitalWrite(OE, HIGH);
	PORTB &= ~_BV(PB0);

	// Initialize all elements to start off
	for (int i = 0; i < NUM_ROWS; i++) 
	{
		rowWords[i] = 0xFFFF;
		rowStateChange[i] = 1;
		for (int j = 0; j < NUM_COLS; j++) 
		{
			stateMatrix[i][j] = 1;
		}
	}

	//SET PWM FREQ TO 31kHz (9&10)
	TCCR1B = TCCR1B & B11111000 | B00000001;
	delay(200);
}

void uMatrix::refreshMatrix(int mDelay) 
{
	for (int i = 0; i < NUM_ROWS; i++) 
	{
		// Check for updates to rows
		// Make updates to each changed row
		// if (rowStateChange[i] == 1) {
			updateMatrixRow(i);
		// }
		
		PORTB &= ~_BV(PB0);       //digitalWrite(_latchPin, LOW);
		
		/*REPLACE THIS WITH CUSTOM SHIFTOUT()*/
		shiftOut(_dataPin, _clockPin, MSBFIRST, (rowWords[i] >> 8));
		shiftOut(_dataPin, _clockPin, MSBFIRST, rowWords[i]);
		shiftOut(_dataPin, _clockPin, MSBFIRST, rows[i]);

		PORTB |= _BV(PB0);        //digitalWrite(_latchPin, HIGH);

		if (mDelay > 0) 
		{
			analogWrite(_OE, mDelay);
		}
		else 
		{
			digitalWrite(_OE, HIGH);
		}

#ifdef DEBUG
		delay(150);
#endif

		// Mark all rows as unchanged if at end of scan
		if (i == (NUM_ROWS - 1)) 
		{
			for (int index = 0; index < NUM_ROWS; index++) 
			{
				rowStateChange[index] = 0;
			}
		}
	}
}

//
// Sets the current pixel values in the row 'buffer'
//
void uMatrix::updateMatrixRow(int row) 
{
	rowWords[row] = 0x0000;
	for (int col = 0; col < NUM_COLS; col++) 
	{
		if (stateMatrix[row][col] == 0) 
		{
			// fill with 1's
			rowWords[row] = (rowWords[row] | (0x0001 << col));
		}
		else 
		{
			// fill with 0's
			rowWords[row] = (rowWords[row] | (0x0000 << col));
		}
	}
}

//
// Sets the specified pixel state.
// Must be called before updateMatrixRow()
//
void uMatrix::setPixelState(int row, int column, _Bool state) 
{
	if(row < NUM_ROWS && column < NUM_COLS)
	{
		if (getPixelState(row, column) != state) 
		{
			stateMatrix[row][column] = state;
			rowStateChange[row] = 1;
		}
	}
}

//
// Sets the specified pixel state.
// Must be called before updateMatrixRow()
//
void uMatrix::setPixelState(int pix, _Bool state) 
{
	if(pix >= 0)
	{
		int row = (pix / 16);
		int column = (pix % 16);
		if (getPixelState(row, column) != state) 
		{
			stateMatrix[row][column] = state;
			rowStateChange[row] = 1;
		}
	}
}

//
// Returns current pixel state
//
_Bool uMatrix::getPixelState(int row, int column) 
{
	if(row < NUM_ROWS && column < NUM_COLS)
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
	for(int i = 0; i <= h; i++)
	{
		if(i == 0)
		{
			for(int j = 1; j < w; j++)
			{
				setPixelState(0, j, 1);
			}
		}
		else if(i == h)
		{
			for(int j = 1; j < w; j++)
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
	if(dist > 0)
	{
		while(count < dist)
		{
			for(int i = 0; i < NUM_ROWS; i++)
			{
				for(int j = NUM_COLS - 1; j >= 0; j--)
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
		while(count < abs(dist))
		{
			for(int i = 0; i < NUM_ROWS; i++)
			{
				for(int j = 0; j < NUM_COLS; j++)
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
	if(dist > 0)
	{
		while(count < dist)
		{
			for(int i = NUM_ROWS - 1; i >= 0; i--)
			{
				for(int j = 0; j < NUM_COLS; j++)
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
		while(count < abs(dist))
		{
			for(int i = 0; i < NUM_ROWS; i++)
			{
				for(int j = 0; j < NUM_COLS; j++)
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

void uMatrix::drawChar(char ch)
{

	switch(ch)
	{
		case '0':
			setPixelState(5, 5, 1);
			break;
		case '1':
			setPixelState(5, 5, 1);
			break;
		case '2':
			setPixelState(5, 5, 1);
			break;
		case '3':
			setPixelState(5, 5, 1);
			break;
		case '4':
			setPixelState(5, 5, 1);
			break;
		case '5':
			setPixelState(5, 5, 1);
			break;
		case '6':
			setPixelState(5, 5, 1);
			break;
		case '7':
			setPixelState(5, 5, 1);
			break;
		case '8':
			setPixelState(5, 5, 1);
			break;
		case '9':
			setPixelState(5, 5, 1);
			break;
		case 'a':
			setPixelState(5, 5, 1);
			break;
		case 'b':
			setPixelState(5, 5, 1);
			break;
		case 'c':
			setPixelState(5, 5, 1);
			break;
		case 'd':
			setPixelState(5, 5, 1);
			break;
		case 'e':
			setPixelState(5, 5, 1);
			break;
		case 'f':
			setPixelState(5, 5, 1);
			break;
		case 'g':
			setPixelState(5, 5, 1);
			break;
		case 'h':
			setPixelState(5, 5, 1);
			break;
		case 'i':
			setPixelState(5, 5, 1);
			break;
		case 'j':
			setPixelState(5, 5, 1);
			break;
		case 'k':
			setPixelState(5, 5, 1);
			break;
		case 'l':
			setPixelState(5, 5, 1);
			break;
		case 'm':
			setPixelState(5, 5, 1);
			break;
		case 'n':
			setPixelState(5, 5, 1);
			break;
		case 'o':
			setPixelState(5, 5, 1);
			break;
		case 'p':
			setPixelState(5, 5, 1);
			break;
		case 'q':
			setPixelState(5, 5, 1);
			break;
		case 'r':
			setPixelState(5, 5, 1);
			break;
		case 's':
			setPixelState(5, 5, 1);
			break;
		case 't':
			setPixelState(5, 5, 1);
			break;
		case 'w':
			setPixelState(5, 5, 1);
			break;
		case 'x':
			setPixelState(5, 5, 1);
			break;
		case 'y':
			setPixelState(5, 5, 1);
			break;
		case 'z':
			setPixelState(5, 5, 1);
			break;
	}
}