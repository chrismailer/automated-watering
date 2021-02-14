int LED = 13;
int moistureSensor = A7;
int sensorValue = 0;

int bias = -64;
int value = 297;

int dryValue = 585;
int wetValue = 295;

int moisturePercent = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop() {
  sensorValue = analogRead(moistureSensor);
  moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
  Serial.println(sensorValue);
  if ((sensorValue < 585) && (sensorValue > 580)) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  delay(500);
}
