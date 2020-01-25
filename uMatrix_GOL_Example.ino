#include <SPI.h>
#include <uMatrix.h>

// STAND. PARAMS
uMatrix myMatrix;
long loopTicks = 1;

// GAME PARAMS
bool golInit = true;
boolean golMat[8][16];
boolean changeMat[8][16];
int stepFreq = 2000;

void setup() {
  SPI.begin();
  randomSeed(analogRead(0));
  myMatrix.initial(8, 12, 11, 9);
  myMatrix.setBrightness(0);
  myMatrix.clearAll();
  myMatrix.refreshMatrix();
}

void loop() {

  if (loopTicks % stepFreq == 0)
  {
    gameOfLife();
  }

  if (loopTicks > 100000)
  {
    loopTicks = 1;
    golInit = true;
  }

  if (loopTicks % 10 == 0)
  {
    myMatrix.refreshMatrix();
  }
  
  loopTicks++;
}


void gameOfLife()
{
  int cell = 0;
  int nayCt = 0;
  int cownt = 0;

  // Initiallize game
  if (golInit)
  {

    for (int i = 0; i < 50; i++)
    {
      int r = random(0, 8); int c = random(0, 16);
      myMatrix.setPixelState(r, c, true);
      setCellState(r, c, true);
    }

    golInit = false;
  }
  else
  {
    for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 16; col++)
      {
        nayCt = 0;

        if (col == 0 && row == 0)
        {
          if (myMatrix.getPixelState((row + 1), col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, (col + 1)))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState((row + 1), (col + 1)))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 15))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 15))
          {
            nayCt++;
          }
        }
        else if (col == 15 && row == 0)
        {
          if (myMatrix.getPixelState((row + 1), col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, (col - 1)))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 15))
          {
            nayCt++;
          }
        }
        else if (row == 7 && col == 0)
        {
          if (myMatrix.getPixelState(row, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 15))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 15))
          {
            nayCt++;
          }
        }
        else if (row == 7 && col == 15)
        {
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 15))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, 0))
          {
            nayCt++;
          }
        }
        else if (row == 0 && col > 0 && col < 15)
        {
          if (myMatrix.getPixelState(row + 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(7, col - 1))
          {
            nayCt++;
          }
        }
        else if (row == 7 && col > 0 && col < 15)
        {
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(0, col - 1))
          {
            nayCt++;
          }
        }
        else if (col == 0 && row > 0 && row < 7)
        {
          if (myMatrix.getPixelState(row + 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, 15))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, 15))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, 15))
          {
            nayCt++;
          }
        }
        else if (col == 15 && row > 0 && row < 7)
        {
          if (myMatrix.getPixelState(row + 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, 0))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, 0))
          {
            nayCt++;
          }
        }
        else
        {
          if (myMatrix.getPixelState(row + 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col - 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row + 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col + 1))
          {
            nayCt++;
          }
          if (myMatrix.getPixelState(row - 1, col - 1))
          {
            nayCt++;
          }
        }
        ///////////////////////////
        if (myMatrix.getPixelState(row, col))
        {
          if (nayCt < 2)
          {
            setCellState(row, col, false);
          }
          else if (nayCt == 2 || nayCt == 3)
          {
            setCellState(row, col, true);
          }
          else if (nayCt >= 4)
          {
            setCellState(row, col, false);
          }
        }
        else
        {
          if (nayCt == 3)
          {
            setCellState(row, col, true);
          }
        }
        /////////////////////
      }
    }
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      if (changeMat[i][j]);
      myMatrix.setPixelState(i, j, golMat[i][j]);
    }
  }
}

void setCellState(int row, int col, boolean stat)
{
  if (golMat[row][col] != stat)
  {
    changeMat[row][col] = true;
    golMat[row][col] = stat;
  }
  else
  {
    changeMat[row][col] = false;
  }
}
