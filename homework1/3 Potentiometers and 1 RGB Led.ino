const int blueInputPin = A0;
const int greenInputPin = A1;
const int redInputPin = A2;

const int blueLedPin = 9;
const int greenLedPin = 10;
const int redLedPin = 11;

int blueInputValue;
int greenInputValue;
int redInputValue;
int blueLedValue;
int greenLedValue;
int redLedValue;

const int maxInitialValue = 1023;
const int minInitialValue = 0;
const int maxValue = 255;
const int minValue = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(blueInputPin, INPUT);
  pinMode(greenInputPin, INPUT);
  pinMode(redInputPin, INPUT);

  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blueInputValue = analogRead(blueInputPin);
  greenInputValue = analogRead(greenInputPin);
  redInputValue = analogRead(redInputPin);

  blueLedValue = map(blueInputValue, minInitialValue, maxInitialValue, minValue, maxValue);
  greenLedValue = map(greenInputValue, minInitialValue, maxInitialValue, minValue, maxValue);
  redLedValue = map(redInputValue, minInitialValue, maxInitialValue, minValue, maxValue);

  analogWrite(blueLedPin, blueLedValue);
  analogWrite(greenLedPin, greenLedValue);
  analogWrite(redLedPin, redLedValue);
}
