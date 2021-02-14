const int led = 13;
const int pump = 12;
const int moistureSensor = A7;

const int numReadings = 10;  //Number of readings averaged for smoothing

int wetPercent = 120;  //When to turn pump off
int dryPercent = 90;  //When to turn pump on

int sensorValue = 0;
int moisturePercent = 0;
int sensorReadings[numReadings];  // array readings from the sensor for smoothing
int readIndex = 0;                // index of the current reading
int total = 0;                    // running total of readings
int averageMoisture = 0;          // average of readings

bool isWatering = false;

//Calibration
int dryValue = 585;
int wetValue = 295;

void setup() {
  pinMode(pump, OUTPUT);
  analogReference(EXTERNAL);
  Serial.begin(9600);
  
  // initialize the readings array:
  for (int index = 0; index < numReadings; index++) {
    sensorValue = analogRead(moistureSensor);
    moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
    sensorReadings[index] = moisturePercent;
    total += moisturePercent;
    delay(100);
  }
}

void loop() {
  
  sensorValue = analogRead(moistureSensor);
  moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
  
  total -= sensorReadings[readIndex];
  sensorReadings[readIndex] = moisturePercent;
  total += sensorReadings[readIndex];
  readIndex ++;
  
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  
  averageMoisture = total / numReadings;
  Serial.println(averageMoisture);

  if (!isWatering && (averageMoisture < dryPercent)) {
    isWatering = true;
    digitalWrite(pump, HIGH);
    digitalWrite(led, HIGH);
  } else if (isWatering && (averageMoisture > wetPercent)) {
    isWatering = false;
    digitalWrite(pump, LOW);
    digitalWrite(led, LOW);
  }
  delay(500);
}
