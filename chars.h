#include "uMatrix.h"

#ifndef CHARS_H
#define CHARS_H

class Chars {
public:
    Chars();
    ~Chars();

    void drawChar(char ch, uMatrix matx);
    
private:
    long charCount, lastCount;
    
};

#endif // !CHARS_H

