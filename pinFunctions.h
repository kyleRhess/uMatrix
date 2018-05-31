#define HIGH 1
#define LOW  0

void setOutputPin(int pin)
{
	switch (pin)
	{
	case 0:
		DDRD = DDRD | 0b00000001;
		break;
	case 1:
		DDRD = DDRD | 0b00000010;
		break;
	case 2:
		DDRD = DDRD | 0b00000100;
		break;
	case 3:
		DDRD = DDRD | 0b00001000;
		break;
	case 4:
		DDRD = DDRD | 0b00010000;
		break;
	case 5:
		DDRD = DDRD | 0b00100000;
		break;
	case 6:
		DDRD = DDRD | 0b01000000;
		break;
	case 7:
		DDRD = DDRD | 0b10000000;
		break;
	case 8:
		DDRB = DDRB | 0b00000001;
		break;
	case 9:
		DDRB = DDRB | 0b00000010;
		break;
	case 10:
		DDRB = DDRB | 0b00000100;
		break;
	case 11:
		DDRB = DDRB | 0b00001000;
		break;
	case 12:
		DDRB = DDRB | 0b00010000;
		break;
	case 13:
		DDRB = DDRB | 0b00100000;
		break;
	default:
		break;
	}
}

void setInputPin(int pin)
{
	switch (pin)
	{
	case 0:
		DDRD = DDRD ^ 0b00000001;
		break;
	case 1:
		DDRD = DDRD ^ 0b00000010;
		break;
	case 2:
		DDRD = DDRD ^ 0b00000100;
		break;
	case 3:
		DDRD = DDRD ^ 0b00001000;
		break;
	case 4:
		DDRD = DDRD ^ 0b00010000;
		break;
	case 5:
		DDRD = DDRD ^ 0b00100000;
		break;
	case 6:
		DDRD = DDRD ^ 0b01000000;
		break;
	case 7:
		DDRD = DDRD ^ 0b10000000;
		break;
	case 8:
		DDRB = DDRB ^ 0b00000001;
		break;
	case 9:
		DDRB = DDRB ^ 0b00000010;
		break;
	case 10:
		DDRB = DDRB ^ 0b00000100;
		break;
	case 11:
		DDRB = DDRB ^ 0b00001000;
		break;
	case 12:
		DDRB = DDRB ^ 0b00010000;
		break;
	case 13:
		DDRB = DDRB ^ 0b00100000;
		break;
	default:
		break;
	}
}

void digWrite(int pin, int state)
{
	if (pin >= 0 && pin <= 7)
	{
		switch (state)
		{
		case HIGH:
			PORTD |= (1 << pin); // high if high
			break;
		case LOW:
			PORTD &= ~(1 << pin); // low if low
			break;
		default:
			break;
		}
	}
	else if (pin >= 8 && pin <= 13)
	{
		switch (state)
		{
		case HIGH:
			PORTB |= (1 << pin - 8); // high if high
			break;
		case LOW:
			PORTB &= ~(1 << pin - 8); // low if low
			break;
		default:
			break;
		}
	}
}

void sendByte(int dataP, int clkP, char data)
{
	digWrite(dataP, LOW);
	for (int i = 7; 0 <= i; i--)
	{
		if (((data >> i) & 0x01)) // get bit from data
			digWrite(dataP, HIGH);
		else
			digWrite(dataP, LOW);

		digWrite(clkP, HIGH);
		digWrite(clkP, LOW);
	}
}