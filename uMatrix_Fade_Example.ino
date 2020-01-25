#include <SPI.h>
#include <uMatrix.h>

uMatrix myMatrix;
long loopTicks = 0;
_Bool flag = 0;

int dir = 0;
int count = 1;

int colBright[16] = {255, 223, 191, 159, 127, 95, 63, 31, 0, 31, 62, 93, 124, 155, 186, 217};

int yPos = 0;
bool rev = false;

void setup() {
  SPI.begin();
  myMatrix.initial(8, 12, 11, 9);
  myMatrix.setBrightness(0);
  myMatrix.clearAll();
  myMatrix.refreshMatrix();
}

void loop() {

  if (loopTicks % 1 == 0)
  {
    myMatrix.clearAll();
    myMatrix.setBrightness(colBright[dir]);
    turnOnColumn(dir++);
  }
  if (dir >= 16) dir = 0;

  if (loopTicks % 60 == 0)
  {
    if (flag)
    {
      int temp = colBright[0];
      for (int i = 0; i < 16 - 1; i++) {
        colBright[i] = colBright[i + 1];
      }
      colBright[16 - 1] = temp;
    }
    else
    {
      int temp = colBright[15];
      for (int i = 15; i > 0; i--) {
        colBright[i] = colBright[i - 1];
      }
      colBright[0] = temp;
    }
  }



  myMatrix.refreshMatrix();
  loopTicks++;
}

void turnOnColumn(int col)
{
  for (int i = 0; i < 8; i++)
  {
    myMatrix.setPixelState(i, col, 1);
  }
}

void turnOffColumn(int col)
{
  for (int i = 0; i < 8; i++)
  {
    myMatrix.setPixelState(i, col, 0);
  }
}
