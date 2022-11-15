#include <EEPROM.h>

// 4 digit 7-segment display pins
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

// shift register pins
const int latchPin  = 11; // STCP
const int clockPin = 10;  // SHCP
const int dataPin = 12; // DS

// joystick pins
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

// value for joystick
int xValue = 0;
int yValue = 0;
const int minThreshold = 400;
const int maxThreshold = 600;
bool joyMoved = false;
bool swState = LOW;
volatile bool buttonPressed = false;

int currentPosition = 0;
bool dpState = LOW;
unsigned long lastBlink = 0;
unsigned int blinkingDuration = 300;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

unsigned long releasedTime = 0;
int pressDuration = 0;
int pressedTime = 0;
unsigned long resetPressDuration = 1500;

const int displayCount = 4;
const int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int noOfDigits = 16;
int byteEncodings[noOfDigits] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int displayEEPROMAddresses[displayCount] {
0, 1, 2, 3
};
int dpEEPROMAddress = 4;

int digitsToBeDisplayed[displayCount] {
  0, 0, 0, 0
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // display pins
  for (int i = 0; i < displayCount; ++i) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), readSWState, FALLING);

  for (int i = 0; i < displayCount; ++i) {
    digitsToBeDisplayed[i] = EEPROM.read(displayEEPROMAddresses[i]);
  }

  currentPosition = EEPROM.read(dpEEPROMAddress);

  Serial.begin(9600);
}

void loop() {
  writeNumber();

  if (buttonPressed) {
    yMove();
  }

  else {
    xMove();
  }

  updateEEPROM();
}

void resetDisplay() {
  digitsToBeDisplayed[0] = 0;
  digitsToBeDisplayed[1] = 0;
  digitsToBeDisplayed[2] = 0;
  digitsToBeDisplayed[3] = 0;
  currentPosition = 0;
}

void readSWState() {
  if (millis() - lastDebounceTime > debounceDelay) {
    buttonPressed = !buttonPressed;

    if (swState == LOW) {
      pressedTime = millis();
    }

    else {
      releasedTime = millis();
    }

    pressDuration = releasedTime - pressedTime;

    if (pressDuration > resetPressDuration && buttonPressed == 0) {
      resetDisplay();
    }
  }

  lastDebounceTime = millis();
}

void writeNumber() {
  for (int i = 0; i < displayCount; ++i) {
    showNumber(i);

    if (i == currentPosition) {
      if (buttonPressed) {
        writeReg(byteEncodings[digitsToBeDisplayed[i]] + 1);
      }

      else {
        blinkingDP();
      }
    }

    else {
      writeReg(byteEncodings[digitsToBeDisplayed[i]]);
    }

    delay(5);
  }
}

void showNumber(int number) {
  for (int i = 0; i < displayCount; ++i) {
    digitalWrite(displayDigits[i], HIGH);
  }

  digitalWrite(displayDigits[number], LOW);
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void yMove() {
  yValue = analogRead(pinY);
  if (yValue < minThreshold && joyMoved == false) {
    if (digitsToBeDisplayed[currentPosition] < noOfDigits - 1) {
      digitsToBeDisplayed[currentPosition]++;
    }
    
    else {
      digitsToBeDisplayed[currentPosition] = 0;
    }

    joyMoved = true;
  }

  if (yValue > maxThreshold && joyMoved == false) {
    if (digitsToBeDisplayed[currentPosition] > 0) {
      digitsToBeDisplayed[currentPosition]--;
    }
    
    else {
      digitsToBeDisplayed[currentPosition] = noOfDigits - 1;
    }
    
    joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }
}

void xMove() {
 xValue = analogRead(pinX);
  if (xValue < minThreshold && joyMoved == false) {
    if (currentPosition < displayCount - 1) {
      currentPosition++;
    }
    
    else {
      currentPosition = 0;
    }
    
    joyMoved = true;
  }
  
  if (xValue > maxThreshold && joyMoved == false) {
    if (currentPosition > 0) {
      currentPosition--;
    }
    
    else {
      currentPosition = displayCount - 1;
    }
    
    joyMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }
}

void blinkingDP(){
  if (millis() - lastBlink > blinkingDuration) {
      dpState = !dpState;
      lastBlink = millis();
  }
  
  if (!dpState) {
    writeReg(byteEncodings[digitsToBeDisplayed[currentPosition]] + 1);
  } 
  
  else {
    writeReg(byteEncodings[digitsToBeDisplayed[currentPosition]]);
  }
}

void updateEEPROM(){
  for(int i = 0; i < displayCount; i++){
    EEPROM.update(i, digitsToBeDisplayed[i]);
    EEPROM.update(4, currentPosition);
  }
}