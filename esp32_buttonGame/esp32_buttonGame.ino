int const numberOfButtons = 5;
const int buttonPins[] = {32, 33, 34, 35, 36};
const int SB = 39; // Start Button Pin
const int ledPins[] = {14, 15, 16, 17, 18};
const int Sled = 19; // Start LED pin

int SBState = 0;
int buttonStates[] = {0,0,0,0,0,0};
int buttonsPushed = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Set each LED pin as output...");
  for (int pin = 0; pin < numberOfButtons; pin++) {
    pinMode(ledPins[pin], OUTPUT);
    Serial.print(pin);
    Serial.println(" pin is set for output");
  }
  pinMode(Sled, OUTPUT);
  Serial.println("Start LED is set for output.");
  Serial.println("Set each button pin as input...");
  for (int pin = 0; pin < numberOfButtons; pin++) {
    pinMode(buttonPins[pin], INPUT);
    Serial.print(pin);
    Serial.println(" pin is set for input");
  }
  pinMode(SB, INPUT);
  Serial.println("Start button is set for input");
  Serial.println("Flashing all leds...");
  int loopCount = 0;
  while (loopCount < numberOfButtons) {
    for (int pin = 0; pin < numberOfButtons; pin++) {
      digitalWrite(ledPins[pin], HIGH);
      delay(100);
      digitalWrite(ledPins[pin], LOW);
    }
    digitalWrite(Sled, HIGH);
    delay(100);
    digitalWrite(Sled, LOW);
    loopCount++;
  }

  Serial.println("Ready to start...");
}

void resetLeds() {
  for (int pin = 0; pin < numberOfButtons; pin++) {
    digitalWrite(ledPins[pin], LOW);
  }
}

void fastButton(int buttonNumber[]) {
  for (int button = 0; button < numberOfButtons; button++) {
    Serial.print(buttonNumber[button]);
    Serial.print(", ");
  }
  while (SBState == HIGH) {
    for (int button = 0; button < numberOfButtons; button++) {
      if (buttonNumber[button] == 1) {
        digitalWrite(ledPins[button], HIGH);
      }
    }
    delay(100);
    SBState = digitalRead(SB);
  }
  memset(buttonStates, 0, sizeof(buttonStates));
  resetLeds();
}

void startGame() {
  while (SBState == HIGH) {
    Serial.println("Waiting for button press...");
    digitalWrite(Sled, HIGH);
    for (int pin = 0; pin < numberOfButtons; pin++) {
      buttonStates[pin] = digitalRead(buttonPins[pin]);
      if (buttonStates[pin] == 1) {
        fastButton(buttonStates);
      }
    }
    SBState = digitalRead(SB);
    delay(50);
  }  
}

void loop() {
  buttonsPushed = 0;
  SBState = digitalRead(SB);
  for (int pin = 0; pin < numberOfButtons; pin++) {
    buttonStates[pin] = digitalRead(buttonPins[pin]);
    buttonsPushed += buttonStates[pin];
  }
  if (buttonsPushed == 0) {
    startGame();
  }

  digitalWrite(Sled, LOW);
  for (int button = 0; button < numberOfButtons; button++){
    Serial.print(buttonStates[button]);
    Serial.print(", ");
  }

  Serial.println("Waiting to start round...");
  Serial.println("------");
  
  delay(1000);
}
