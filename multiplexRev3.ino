//#define DEBUG


// PREP FOR FAST ANALOGREAD
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int rightButPin = 10;
int leftButPin = 9;

int outputEnable = 9;
int mDelay = 100;
boolean mDel = false;
boolean hi = false;
long lastTime = 0;

int rows[] = {1, 2, 4, 8, 16, 32, 64, 128}; //Row bytes (known)

boolean matrix[8][16];

String rowBytes[8][2]; // left and right column bytes
boolean rowStateChange[8];

int del = 100;

String rightCol = "";
String leftCol = "";

long count;
int prevX;
int prevY;
boolean shift = false;
int ind = 0;


int hunds = 0;
int tens = 0;
int ones = 0;
int ten = 80;

int player[2];
boolean gameOver = true;
int score = 0;
long prevPixTime = 0;
long prevEnemyTime = 0;
long prevPlayerTime = 0;
long gameStartTime = 0;
int life = 3;
int spawnFactor;
boolean rightButState = false;
boolean lastRightState = false;
boolean leftButState = false;
boolean lastLeftState = false;

int snowM[8] = {15, 15, 15, 15, 15, 15, 15, 15};
int frame = 0;
int frame2 = 0;

int counter = 0;

long prevTime = 0;

boolean golInit = true;
boolean golMat[8][16];
boolean changeMat[8][16];
int gCount = 0;

boolean mDe = true;

void setup() {
  // INCREASE analogRead() SPEED
  sbi(ADCSRA, ADPS2) ;
  cbi(ADCSRA, ADPS1) ;
  cbi(ADCSRA, ADPS0) ;

  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(outputEnable, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(rightButPin, INPUT);
  pinMode(leftButPin, INPUT);
  randomSeed(analogRead(A0));

  digitalWrite(outputEnable, HIGH);
  PORTB &= ~_BV(PB0);

  //Serial.begin(115200);

  // Initialize all elements to start off
  for (int i = 0; i < 8; i++) {
    rowBytes[i][0] = "11111111";
    rowBytes[i][1] = "11111111";
  }
  player[0] = 4;
  player[1] = 15;
  //tShape(2, 1, true);



  // GAME SETUP
  //  setPixelState(player[0], player[1], true);
  //  setPixelState(player[0], player[1] - 1, true);
  //  for (int i = 0; i < 5; i++) {
  //    setPixelState(i, 4, true);
  //    setPixelState(1, 3, true);
  //    setPixelState(1, 5, true);
  //    setPixelState(2, 2, true);
  //    setPixelState(2, 6, true);
  //  }
  /////////////////////////

  //  int r1 = 7-random(0, 7);
  //  int r2 = 7-random(0, 7);
  //  int c1 = 15-random(0, 15);
  //  int c2 = 15-random(0, 15);
  //  if (c1 >= c2) {
  //    int temp = c2;
  //    c2 = c1;
  //    c1 = temp;
  //  }
  //  if (r1 >= r2) {
  //    int temp = r2;
  //    r2 = r1;
  //    r1 = temp;
  //  }
  //  makeRect(r1, c1, r2, c2);
  pinMode(A1, INPUT);
  mDelay = 245;

  //SET PWM FREQ TO 31kHz (9&10)
  TCCR1B = TCCR1B & B11111000 | B00000001;
  delay(200);
  digitalWrite(outputEnable, LOW);
}

void loop() {
  //dodgeGame();
  //mDelay = map(analogRead(A1), 0, 1023, 0, 254);
  //int a = random(0, 9999);

  //  if (gCount >= 200) {
  //    clearAll();
  //    gCount = 0;
  //    golInit = true;
  //randomSeed(analogRead(A0));
  //    gameOfLife();
  //  } else {
  //    gameOfLife();
  //    gCount++;
  //  }

  //  float mA = 507.0 - (float)analogRead(A2);
  //  mA = mA * 50.0;
  //  mA = mA / 1023.0;
  //int mA = (analogRead(A1) * (5000/1024));
  //Serial.println((512.0 - (float)analogRead(A3)) * 50 / 1023);

  if (mDe) {
    mDelay--;
    if (mDelay <= 2) {
      mDe = !mDe;
    }
  } else {
    mDelay++;
    if (mDelay >= 255) {
      mDe = !mDe;
    }

  }
  setPixelState(random(0, 8), random(0, 16), true);
  setPixelState(random(0, 8), random(0, 16), false);
  setPixelState(random(0, 8), random(0, 16), false);
  //makeNum(random(9999));
  //    if ((millis() - lastTime) >= 10) {
  //    //clearAll();
  //    //    snow();
  //    setPixelState(random(0, 8), 0, true);
  //  lastTime = millis();
  //    //mDelay = map(analogRead(A2), 40, 1000, 5, 250);
  //    //    if (millis() > 5000) {
  //    //      setPixelState(random(0, 8), 15, false);
  //    // drawLine(0, 0, random(1, 15), random(1, 15));
  //    mDel = !mDel;
  //
  //    //Random boxes
  //    clearAll();
  //    int r1 = random(0, 8);
  //    int r2 = random(0, 8);
  //    int c1 = random(0, 16);
  //    int c2 = random(0, 16);
  //    if (c1 >= c2) {
  //      int temp = c2;
  //      c2 = c1;
  //      c1 = temp;
  //    }
  //    if (r1 >= r2) {
  //      int temp = r2;
  //      r2 = r1;
  //      r1 = temp;
  //    }
  //    makeRect(r1, c1, r2, c2);
  //    }

  //
  //    if (mDel) {
  //      mDelay++;
  //      delay(5);
  //    } else {
  //      mDelay--;
  //      delay(5);
  //    }

  //      clearAll();
  //      makeRect(0 + frame, 0 + (frame * 2), 7 - frame, 15 - (frame * 2));
  //      if (frame >= 2) {
  //       // makeRect(0 + (frame - 2), 0 + ((frame - 2) * 2), 7 - (frame - 2), 15 - ((frame - 2) * 2));
  //      }
  //      frame++;
  //      if (frame >= 4) {
  //        frame = 0;
  //      }
  //      makeRect(0 + frame+1, 0 + (frame * 2)+1, 7 - frame-1, 15 - (frame * 2)-1);

  ///SCANNER viz
  //  if (mDel) {
  //    counter--;
  //    if (counter < 14) {
  //      turnOffCol(counter + 1);
  //    }else{
  //      turnOffCol(0);
  //    }
  //  } else {
  //    counter++;
  //    if (counter > 0) {
  //      turnOffCol(counter - 1);
  //    }else{
  //      turnOffCol(15);
  //    }
  //  }
  //  if (counter > 15) {
  //    mDel = true;
  //  } else if (counter < 0) {
  //    mDel = false;
  //  }
  //
  //  turnOnCol(counter);
  //  delay(3);
  //while (millis() - prevTime < map(analogRead(A1), 0, 1024, 3, 300)) {////////////////
  for (int i = 0; i < 8; i ++) { // Go through rows

    PORTB &= ~_BV(PB0); //digitalWrite(latchPin, LOW);

    if (rowStateChange[i]) { // Check for updates to rows
      updateMatrixRow(i); // Make updates to each changed row
    }

    shiftOut(dataPin, clockPin, MSBFIRST, strtoul(rowBytes[i][0].c_str(), NULL, 2));
    shiftOut(dataPin, clockPin, MSBFIRST, strtoul(rowBytes[i][1].c_str(), NULL, 2));
    shiftOut(dataPin, clockPin, MSBFIRST, rows[i]);

    PORTB |= _BV(PB0);  //digitalWrite(latchPin, HIGH);
    if (mDelay > 0) {
      //      digitalWrite(outputEnable, LOW);
      //      delayMicroseconds(mDelay);
      //      digitalWrite(outputEnable, HIGH);
      analogWrite(outputEnable, mDelay);
    } else {
      digitalWrite(outputEnable, HIGH);
    }
#ifdef DEBUG
    delay(del);
#endif

    // Mark all rows as unchanged if at end of scan
    if (i == 7) {
      for (int index = 0; index < 8; index++) {
        rowStateChange[index] = false;
      }
    }
    count++;
  }
  //}////////////////
  prevTime = millis();
}

void tShape(int xOrg, int yOrg, boolean state) {
  setPixelState(xOrg, yOrg, state);
  setPixelState(xOrg + 1, yOrg, state);
  setPixelState(xOrg + 1, yOrg + 1, state);
  setPixelState(xOrg + 2, yOrg, state);
}

void turnOnCol(int col)
{
  for (int i = 0; i < 8; i++) {
    setPixelState(i, col, true);
  }
}
void turnOffCol(int col)
{
  for (int i = 0; i < 8; i++) {
    setPixelState(i, col, false);
  }
}

void updateMatrixRow(int row) {
  rightCol = "";
  leftCol = "";

  //SPEAKER 'CLICK' PER CHANGE FOR DEBUGGING
#ifdef DEBUG
  PORTD |= _BV(PD7);
  delayMicroseconds(80);
  PORTD &= ~_BV(PD7);
#endif

  for (int col = 0; col < 16; col++) {
    if (!matrix[row][col]) {
      if (col < 8) {
        rightCol += "1";
      } else {
        leftCol += "1";
      }
    } else {
      if (col < 8) {
        rightCol += "0";
      } else {
        leftCol += "0";
      }
    }
  }
  rowBytes[row][0] = rightCol;
  rowBytes[row][1] = leftCol;
}

void setPixelState(int row, int column, boolean state) {
  if (getPixelState(row, column) == state) {
    //
  } else {
    matrix[row][15 - column] = state;
    rowStateChange[row] = true;
  }
}

boolean getPixelState(int row, int column) {
  return matrix[row][15 - column];
}


void makeRect(int r1, int c1, int r2, int c2)
{
  for (int i = r1; i <= r2; i++)
  {
    for (int j = c1; j <= c2; j++)
    {
      if (i == r1) {
        setPixelState(i, j, true);
      } else if (i != r2) {
        setPixelState(i, c1, true);
        setPixelState(i, c2, true);
      } else {
        setPixelState(i, j, true);
      }
    }
  }
}

void drawLine(int r1, int c1, int r2, int c2)
{
  float dx = r2 - r1;
  float dy = c2 - c1;
  float slope = dy / dx;
  //Serial.println(slope);


  for (int i = r1; i <= r2; i++) {
    for (int j = 0; j < 16; j++) {
      if ((round(slope * i) - j) == 1 || (round(slope * i) - j) == 0) {
        setPixelState(i, j, true);
      }
    }
  }

}

void shiftScreenLeft(int xRange[2], int yRange[2], int spaces) {
  for (int i = xRange[0]; i <= xRange[1]; i++) {
    for (int j = yRange[0]; j <= yRange[1]; j++) {
      if (j - spaces > 0) {
        setPixelState(i, j - spaces, getPixelState(i, j));
        setPixelState(i, j, !getPixelState(i, j));
        //        if (j == yRange[1]) {
        //          setPixelState(i, j, !getPixelState(i, j));
        //        }
      }
    }
  }
}

void shiftScreenRight(int spaces) {
  int count;
  while (count < spaces) {
    for (int i = 0; i < 8; i++) {
      for (int j = 15; j >= 0; j--) {
        if (j != 0) {
          setPixelState(i, j, getPixelState(i, j - 1));
        } else {
          setPixelState(i, j, false);
        }
      }
    }
    count++;
  }
}

void shiftScreenUp(int spaces) {
  int count;
  while (count < spaces) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        if (i != 7) {
          setPixelState(i, j, getPixelState(i + 1, j));
        } else {
          setPixelState(i, j, false);
        }
      }
    }
    count++;
  }
}

void shiftScreenDown(int spaces) {
  int count;
  while (count < spaces) {
    for (int i = 7; i >= 0; i--) {
      for (int j = 0; j < 16; j++) {
        if (i != 0) {
          setPixelState(i, j, getPixelState(i - 1, j));
        } else {
          setPixelState(i, j, false);
        }
      }
    }
    count++;
  }
}


void clearAll() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      setPixelState(i, j, false);
    }
  }
}


void swapPixel(int row, int column, int x, int y) {
  setPixelState(x, y, getPixelState(row, column));
  setPixelState(row, column, !getPixelState(row, column));
}



boolean shiftEnemy() {
  boolean temp = false;
  for (int i = 0; i < 8; i++) {
    for (int j = 15; j >= 0; j--) {
      if (j > 2) {
        if (i == player[0] && j == player[1] && getPixelState(i, j - 2)) {
          temp = true;
        }
        setPixelState(i, j, getPixelState(i, j - 1));
      } else {
        setPixelState(i, j, false);
      }
    }
  }
  return temp;
}


void snow() {

  for (int i = 0; i < 8; i++) {
    for (int j = snowM[i]; j >= 1; j--) {
      if (snowM[i] == 0) {
        snowM[i] = 15;
      } else {
        if (j == 15 && getPixelState(i, j)) {
          snowM[i] == 14;
        } else if (getPixelState(i, j - 1) &&  j == snowM[i]) {
          snowM[i] = j - 1;
          setPixelState(i, j, getPixelState(i, j - 1));
          setPixelState(i, j - 1, false);
        } else {
          setPixelState(i, j, getPixelState(i, j - 1));
          setPixelState(i, j - 1, false);
        }
      }
    }
  }
}






void dodgeGame() {
  long currentTime = millis();
  if (gameOver && digitalRead(rightButPin)) {

    gameOver = false;
    clearAll();
    count = 0;
    life = 3;
    spawnFactor = random(90, 120);
    gameStartTime = currentTime;
  }
  if (!gameOver) {
    score = count / 100;
    if ((currentTime - prevPixTime) >= spawnFactor) {
      setPixelState(random(0, 8), 2, true);
      prevPixTime = millis();
    }
    long expon = 200 - (6 * ((currentTime - gameStartTime) / 1000));
    if (expon < 15) {
      expon = 15;
    }
    if ((currentTime - prevEnemyTime) >= expon) {
      clicker();
      if (score % (life * 100) == 0 && score > 100) {
        life++;
        for (int i = 0; i < 500; i++) {
          PORTD |= _BV(PD7);
          delayMicroseconds(40);
          PORTD &= ~_BV(PD7);
          delayMicroseconds(40);
        }
      }
      if (shiftEnemy()) {
        life--;
        for (int i = 0; i < 3000; i++) {
          PORTD |= _BV(PD7);
          delayMicroseconds(80);
          PORTD &= ~_BV(PD7);
        }
        if (life <= 0) {
          gameOver = true;
          //Serial.println(score);
          clearAll();
          for (int i = 0; i < 3000; i++) {
            PORTD |= _BV(PD7);
            delayMicroseconds(60);
            PORTD &= ~_BV(PD7);
            delayMicroseconds(60);
          }

          int dig = 4;
          while (score > 0) {
            displayNum(dig, score % 10);
            score = score / 10;
            dig--;
          }
          for (int i = 0; i < 5; i++) {
            setPixelState(i, 2, true);
            setPixelState(1, 1, true);
            setPixelState(1, 3, true);
            setPixelState(2, 0, true);
            setPixelState(2, 4, true);
          }
        }

      }
      prevEnemyTime = millis();
    }
    if ((currentTime - prevPlayerTime) >= 100) {
      if (digitalRead(rightButPin)  && player[0] != 0) {
        setPixelState(player[0], player[1], false);
        setPixelState(player[0], player[1] - 1, false);
        player[0] = player[0] - 1;
      }
      if (digitalRead(leftButPin) && player[0] != 7) {
        setPixelState(player[0], player[1], false);
        setPixelState(player[0], player[1] - 1, false);
        player[0] = player[0] + 1;
      }
      prevPlayerTime = millis();
    }
    setPixelState(player[0], player[1], true);
    setPixelState(player[0], player[1] - 1, true);
  }
  for (int i = 7; i > 7 - life; i--) {
    setPixelState(i, 0, true);
  }
}





void makeNum(int num) {
  clearAll();
  if (num == 0) {
    displayNum(4, 0);
  } else {
    int n = 4;
    while (num > 0) {
      displayNum(n, num % 10);
      num = num / 10;
      n--;
    }
  }
}









void displayNum(int dig, int n) {
  int shift = (dig - 1) * 4;
  for (int i = 1; i < 7; i++) {
    setPixelState(i, 1 + shift, false);
    if (i == 1 || i == 3 || i == 6) {
      setPixelState(i, 2 + shift, false);
    }
    setPixelState(i, 3 + shift, false);
  }
  if (n == 0) {
    for (int i = 1; i < 7; i++) {
      setPixelState(i, 1 + shift, true);
      if (i == 1 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 9) {
    for (int i = 1; i < 7; i++) {
      if (i < 4) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 1 || i == 3) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 8) {
    for (int i = 1; i < 7; i++) {

      setPixelState(i, 1 + shift, true);

      if (i == 1 || i == 3 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 7) {
    for (int i = 1; i < 7; i++) {
      if (i == 1) {
        setPixelState(i, 1 + shift, true);
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 6) {
    for (int i = 1; i < 7; i++) {

      setPixelState(i, 1 + shift, true);

      if (i == 1 || i == 3 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      if (i != 2) {
        setPixelState(i, 3 + shift, true);
      }
    }
  }
  if (n == 5) {
    for (int i = 1; i < 7; i++) {
      if (i != 4 && i != 5) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 1 || i == 3 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      if (i != 2) {
        setPixelState(i, 3 + shift, true);
      }
    }
  }
  if (n == 4) {
    for (int i = 1; i < 7; i++) {
      if (i != 4 && i != 5 && i != 6) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 3) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 4) {
    for (int i = 1; i < 7; i++) {
      if (i != 4 && i != 5 && i != 6) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 3) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 3) {
    for (int i = 1; i < 7; i++) {
      if (i != 2 && i != 4 && i != 5) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 3 || i == 1 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  if (n == 2) {
    for (int i = 1; i < 7; i++) {
      if (i != 2) {
        setPixelState(i, 1 + shift, true);
      }
      if (i == 3 || i == 1 || i == 6) {
        setPixelState(i, 2 + shift, true);
      }
      if (i != 4 && i != 5) {
        setPixelState(i, 3 + shift, true);
      }
    }
  }
  if (n == 1) {
    for (int i = 1; i < 7; i++) {
      if (i == 1) {
        setPixelState(i, 2 + shift, true);
      }
      setPixelState(i, 3 + shift, true);
    }
  }
  // Colon separator
  //  setPixelState(2, 8, true);
  //  setPixelState(5, 8, true);
}



void gameOfLife() {
  int cell = 0;
  int nayCt = 0;
  int cownt = 0;

  // Initiallize game
  if (golInit) {

    for (int i = 0; i < 50; i++) {
      int r = random(0, 8); int c = random(0, 16);
      setPixelState(r, c, true);
      setCellState(r, c, true);
    }
    //    setPixelState(4, 4, true);
    //    setPixelState(4, 5, true);
    //    setPixelState(4, 6, true);
    //    setPixelState(5, 3, true);
    //    setPixelState(5, 4, true);
    //    setPixelState(5, 5, true);
    //    setCellState(4, 4, true);
    //    setCellState(4, 5, true);
    //    setCellState(4, 6, true);
    //    setCellState(5, 3, true);
    //    setCellState(5, 4, true);
    //    setCellState(5, 5, true);
    golInit = false;
  } else {
    for (int gRows = 0; gRows < 8; gRows++) {
      for (int gCols = 0; gCols < 16; gCols++) {
        nayCt = 0;

        if (gCols == 0 && gRows == 0) {
          if (getPixelState((gRows + 1), gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, (gCols + 1))) {
            nayCt++;
          }
          if (getPixelState((gRows + 1), (gCols + 1))) {
            nayCt++;
          }
          if (getPixelState(7, 0)) {
            nayCt++;
          }
          if (getPixelState(0, 15)) {
            nayCt++;
          }
          if (getPixelState(7, 15)) {
            nayCt++;
          }
        } else if (gCols == 15 && gRows == 0) {
          if (getPixelState((gRows + 1), gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, (gCols - 1))) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(7, 0)) {
            nayCt++;
          }
          if (getPixelState(0, 0)) {
            nayCt++;
          }
          if (getPixelState(7, 15)) {
            nayCt++;
          }
        } else if (gRows == 7 && gCols == 0) {
          if (getPixelState(gRows, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(0, 0)) {
            nayCt++;
          }
          if (getPixelState(0, 15)) {
            nayCt++;
          }
          if (getPixelState(7, 15)) {
            nayCt++;
          }
        } else if (gRows == 7 && gCols == 15) {
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(7, 0)) {
            nayCt++;
          }
          if (getPixelState(0, 15)) {
            nayCt++;
          }
          if (getPixelState(0, 0)) {
            nayCt++;
          }
        } else if (gRows == 0 && gCols > 0 && gCols < 15) {
          if (getPixelState(gRows + 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(7, gCols)) {
            nayCt++;
          }
          if (getPixelState(7, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(7, gCols - 1)) {
            nayCt++;
          }
        } else if (gRows == 7 && gCols > 0 && gCols < 15) {
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(0, gCols)) {
            nayCt++;
          }
          if (getPixelState(0, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(0, gCols - 1)) {
            nayCt++;
          }
        } else if (gCols == 0 && gRows > 0 && gRows < 7) {
          if (getPixelState(gRows + 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows, 15)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, 15)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, 15)) {
            nayCt++;
          }
        } else if (gCols == 15 && gRows > 0 && gRows < 7) {
          if (getPixelState(gRows + 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows, 0)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, 0)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, 0)) {
            nayCt++;
          }
        } else {
          if (getPixelState(gRows + 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols - 1)) {
            nayCt++;
          }
          if (getPixelState(gRows + 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols + 1)) {
            nayCt++;
          }
          if (getPixelState(gRows - 1, gCols - 1)) {
            nayCt++;
          }
        }
        ///////////////////////////
        if (getPixelState(gRows, gCols)) {
          if (nayCt < 2) {
            setCellState(gRows, gCols, false);
          } else if (nayCt == 2 || nayCt == 3) {
            setCellState(gRows, gCols, true);
          } else if (nayCt >= 4) {
            setCellState(gRows, gCols, false);
          }
        } else {
          if (nayCt == 3) {
            setCellState(gRows, gCols, true);
          }
        }
        /////////////////////
      }
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      if (changeMat[i][j])
        setPixelState(i, j, golMat[i][j]);
    }
  }
}


//int checkCount(int r, int c) {
//  if (gCols == 15 && gRows > 0 && gRows < 7) {
//    if (getPixelState(gRows + 1, gCols)) {
//      nayCt++;
//    }
//    if (getPixelState(gRows - 1, gCols)) {
//      nayCt++;
//    }
//    if (getPixelState(gRows, gCols - 1)) {
//      nayCt++;
//    }
//    if (getPixelState(gRows + 1, gCols - 1)) {
//      nayCt++;
//    }
//    if (getPixelState(gRows - 1, gCols - 1)) {
//      nayCt++;
//    }
//  }
//}

void setCellState(int row, int col, boolean stat) {
  if (golMat[row][col] != stat) {
    changeMat[row][col] = true;
    golMat[row][col] = stat;
  } else {
    changeMat[row][col] = false;
  }
}


void clicker() {
  PORTD |= _BV(PD7);
  delayMicroseconds(80);
  PORTD &= ~_BV(PD7);
}


