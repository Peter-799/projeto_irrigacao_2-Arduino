const unsigned long segundo = 1000;
const unsigned long minuto = 60000;
const unsigned long hora = 3600000;

const int ledPin = 13;

unsigned long previousMillis = 0;
int comando = -1;
float tempoOn = 0;
float tempoOff = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if (Serial.available()) {
    comando  = Serial.readStringUntil(',').toFloat();
    tempoOn  = Serial.readStringUntil(',').toFloat();
    tempoOff = Serial.readStringUntil('\n').toFloat();
    previousMillis = millis();
  }

  switch (comando) {
    case 0:
      digitalWrite(ledPin, LOW);
      break;

    case 1:
      digitalWrite(ledPin, HIGH);
      break;

    case 2:
      if (comando != 2) break;
      if (digitalRead(ledPin) == LOW) {
        if (millis() - previousMillis >= tempoOff * segundo) {
          previousMillis = millis();
          digitalWrite(ledPin, HIGH);
        }
      } else {
        if (millis() - previousMillis >= tempoOn * segundo) {
          previousMillis = millis();
          digitalWrite(ledPin, LOW);
        }
      }
      break;
  }
}
