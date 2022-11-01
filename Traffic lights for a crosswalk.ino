const int buttonPin = 2;

const int buzzerPin = 4;

const int redPasserLedPin = 6;
const int greenPasserLedPin = 7;
const int greenCarLedPin = 8;
const int yellowCarLedPin = 9;
const int redCarLedPin = 10;

// button initial state
bool buttonState = LOW;

// leds intial states: red -> pedestrians, green -> cars
bool redPasserLedState = HIGH;
bool greenPasserLedState = LOW;
bool greenCarLedState = HIGH;
bool yellowCarLedState = LOW;
bool redCarLedState = LOW;

// buzzer intial state
bool buzzerState = LOW;

// for reading the button
bool pressedButton = 0;
bool reading = HIGH;
bool previousReading = HIGH;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

// for starting the buzzer 
int buzzerTone = 1500;
int toneDuration = 10;
unsigned int buzzerInterval = 1000;
unsigned int buzzerIntermittentInterval = 500;
unsigned int lastBuzzerPlay = 0;

// for blinking green
unsigned int lastGreenBlink = 0;
unsigned int blinkDuration = 500;

// states intervals
unsigned long startCrosswalk = 0;
unsigned int stateOneInterval = 10000;
unsigned int stateTwoInterval = 13000;
unsigned int stateThreeInterval = 23000;
unsigned int stateFourInterval = 28000;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(redPasserLedPin, OUTPUT);
  pinMode(greenPasserLedPin, OUTPUT);
  pinMode(greenCarLedPin, OUTPUT);
  pinMode(yellowCarLedPin, OUTPUT);
  pinMode(redCarLedPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(greenCarLedPin, greenCarLedState);
  digitalWrite(yellowCarLedPin, yellowCarLedState);
  digitalWrite(redCarLedPin, redCarLedState);
  digitalWrite(greenPasserLedPin, greenPasserLedState);
  digitalWrite(redPasserLedPin, redPasserLedState);

  readingButton();

  if  (pressedButton) {
    if (millis() - startCrosswalk > stateOneInterval && greenCarLedState) {
      // 10s after pressing the button
      state2();
    }

    else if (millis() - startCrosswalk > stateTwoInterval && yellowCarLedState) {
      state3();
    }

    else if (millis() - startCrosswalk > stateThreeInterval && millis() - startCrosswalk <= stateFourInterval && redCarLedState) {
      // intermittent green for pedestrians and buzzer beeping faster
      state4();
    }

    else if (millis() - startCrosswalk > stateFourInterval) {
      // default state untill the button is pressed again 
      state1();
    }

    playBuzzer();
  }
}

void readingButton() {
  // reading the state of the button
  reading = digitalRead(buttonPin);

  // check the prev state
  if (reading != previousReading) {
    lastDebounceTime = millis();
  }

  // check if the button was pressed
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // check if the button was not pressed before
      if (buttonState == LOW && !pressedButton) {
        pressedButton = 1;
        startCrosswalk = millis();
      }
    }
  }

  previousReading = reading;
}

void state1() {
  // red for pedestrians, green for cars
  // duration: indefinite
  greenPasserLedState = LOW;
  redPasserLedState = !redPasserLedState;
  greenCarLedState = !greenCarLedState;
  redCarLedState = !redCarLedState;

  pressedButton = 0;
}

void state2() {
  // red for pedestrians, yellow for cars
  // duration: 3s
  greenCarLedState = !greenCarLedState;
  yellowCarLedState = !yellowCarLedState;
}

void state3() {
  // green for pedestrians, red for cars
  // duration: 10s
  yellowCarLedState = !yellowCarLedState;
  redCarLedState = !redCarLedState;
  greenPasserLedState = !greenPasserLedState;
  redPasserLedState = !redPasserLedState;
  buzzerState = !buzzerState;
}

void state4() {
  // blinking green for pedestrians, red for cars
  // duration: 5s
  if (millis() - lastGreenBlink > blinkDuration) {
    greenPasserLedState = !greenPasserLedState;
    lastGreenBlink = millis();
  }
}

void playBuzzer() {
  Serial.println(millis() - startCrosswalk);

  if (buzzerState) {
    if (millis() - startCrosswalk > stateFourInterval) {
      // it stops
      state1();
    }

    else if (millis() - startCrosswalk > stateThreeInterval && millis() - lastBuzzerPlay > buzzerIntermittentInterval) {
      // it starts playing faster
      tone(buzzerPin, buzzerTone, toneDuration);
      lastBuzzerPlay = millis();
    }

    else if (millis() - startCrosswalk > stateTwoInterval && millis() - lastBuzzerPlay > buzzerInterval) {
      // it starts playing
      tone(buzzerPin, buzzerTone, 10);
      lastBuzzerPlay = millis();
    }
  }
}