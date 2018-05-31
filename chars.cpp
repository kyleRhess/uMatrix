#include "chars.h"
#include "uMatrix.h"

//<<constructor>>
Chars::Chars(){}

//<<deconstructor>>
Chars::~Chars() {}

void Chars::drawChar(char ch, uMatrix matx)
{
    // keep track of number of chars printed
    matx.offsetX(0 - lastCount);
    lastCount = 0;

    switch(ch)
    {
        case '0':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(4, 14, 1);
            lastCount = 3;
            break;
        case '1':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(5, 13, 1);
            lastCount = 3;
            break;
        case '2':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(4, 15, 1);
            lastCount = 3;
            break;
        case '3':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(3, 15, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case '4':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(4, 15, 1);
            lastCount = 3;
            break;
        case '5':
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            lastCount = 3;
            break;
        case '6':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 15, 1);
            lastCount = 3;
            break;
        case '7':
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(7, 14, 1);
            lastCount = 3;
            break;
        case '8':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 13, 1);
            lastCount = 3;
            break;
        case '9':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 13, 1);
            lastCount = 3;
            break;
        case 'a':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 12, 1);
            matx.setPixelState(6, 12, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(5, 12, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 14, 1);
            lastCount = 4;
            break;
        case 'A':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 14, 1);
            lastCount = 3;
            break;
        case 'b':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'B':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 12, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 12, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 12, 1);
            matx.setPixelState(4, 12, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(3, 12, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 4;
            break;
        case 'c':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            lastCount = 3;
            break;
        case 'C':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 13, 1);
            matx.setPixelState(3, 14, 1);
            lastCount = 3;
            break;
        case 'd':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(3, 15, 1);
            lastCount = 3;
            break;
        case 'D':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'e':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            lastCount = 3;
            break;
        case 'E':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 13, 1);
            matx.setPixelState(3, 14, 1);
            lastCount = 3;
            break;
        case 'f':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 15, 1);
            lastCount = 3;
            break;
        case 'F':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 15, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'g':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(3, 14, 1);
            lastCount = 3;
            break;
        case 'G':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 12, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 12, 1);
            matx.setPixelState(5, 12, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(4, 12, 1);
            matx.setPixelState(3, 12, 1);
            matx.setPixelState(3, 13, 1);
            matx.setPixelState(3, 14, 1);
            lastCount = 4;
            break;
        case 'h':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'H':
            // matx.setPixelState(7, 15, 1);
            // matx.setPixelState(7, 13, 1);
            // matx.setPixelState(6, 15, 1);
            // matx.setPixelState(6, 13, 1);
            // matx.setPixelState(5, 15, 1);
            // matx.setPixelState(5, 14, 1);
            // matx.setPixelState(5, 13, 1);
            // matx.setPixelState(4, 13, 1);
            // matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'i':
            matx.setPixelState(5, 5, 1);
            break;
        case 'j':
            matx.setPixelState(5, 5, 1);
            break;
        case 'k':
            matx.setPixelState(5, 5, 1);
            break;
        case 'l':
            matx.setPixelState(5, 5, 1);
            break;
        case 'm':
            matx.setPixelState(5, 5, 1);
            break;
        case 'n':
            matx.setPixelState(5, 5, 1);
            break;
        case 'o':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 15, 1);
            lastCount = 3;
            break;
        case 'O':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 13, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 3;
            break;
        case 'p':
            matx.setPixelState(5, 5, 1);
            break;
        case 'q':
            matx.setPixelState(5, 5, 1);
            break;
        case 'r':
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 13, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 15, 1);
            lastCount = 3;
            break;
        case 'R':
            matx.setPixelState(7, 15, 1);
            matx.setPixelState(7, 12, 1);
            matx.setPixelState(6, 14, 1);
            matx.setPixelState(6, 12, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 12, 1);
            matx.setPixelState(4, 15, 1);
            matx.setPixelState(4, 12, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 4;
            break;
        case 's':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(4, 14, 1);
            matx.setPixelState(4, 15, 1);
            lastCount = 3;
            break;
        case 'S':
            matx.setPixelState(7, 14, 1);
            matx.setPixelState(7, 13, 1);
            matx.setPixelState(7, 12, 1);
            matx.setPixelState(6, 15, 1);
            matx.setPixelState(5, 14, 1);
            matx.setPixelState(5, 13, 1);
            matx.setPixelState(5, 12, 1);
            matx.setPixelState(4, 12, 1);
            matx.setPixelState(3, 14, 1);
            matx.setPixelState(3, 13, 1);
            lastCount = 4;
            break;
        case 't':
            matx.setPixelState(5, 5, 1);
            break;
        case 'u':
            matx.setPixelState(5, 5, 1);
            break;
        case 'v':
            matx.setPixelState(5, 5, 1);
            break;
        case 'w':
            matx.setPixelState(5, 5, 1);
            break;
        case 'x':
            matx.setPixelState(5, 5, 1);
            break;
        case 'y':
            matx.setPixelState(5, 5, 1);
            break;
        case 'z':
            matx.setPixelState(5, 5, 1);
            break;
    }
    matx.offsetX(-1);
    //charCount++;
}