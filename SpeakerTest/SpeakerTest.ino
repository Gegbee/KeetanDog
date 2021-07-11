#define leftPin 0
#define rightPin 1
#define leftLEDPin 2;
#define rightLEDPin 3;

void setup() {
  pinMode(leftLEDPin, OUTPUT);
  pinMode(rightLEDPin, INPUT);
}

void loop() {
  int leftInput = analogRead(leftPin);
  int rightInput = analogRead(rightPin);
  if (leftInput > threshold) {
    digitalWrite(leftLEDPin, HIGH);
  } else {
    digitalWrite(leftLEDPin, LOW);
  }
  if (rightInput > threshold) {
    digitalWrite(rightLEDPin, HIGH);
  } else {
    digitalWrite(rightLEDPin, LOW);
  }

}
