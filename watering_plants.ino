//sketch designed for the resistive moisture sensor YL-69 sensor.
//it's recommended to use this sensor without a continuous VCC

int moistReadpin = A0; //moist sensor reading pin
int moistPowerpin = 3;
int pumpPin = 2; //triggers pump to work

int okLED = 5; 
int wateringLED = 6;

int sensorValue; //reading from the sensor
int dryLimit = 886; //this depends on the sensor

void setup(){
     pinMode(pumpPin, OUTPUT);
     pinMode(okLED, OUTPUT);
     pinMode(wateringLED, OUTPUT);
     pinMode(moistPowerpin, OUTPUT);
     Serial.begin(9600);
     runTests(); //runs series of tests to the main components.
     Serial.println("Starting reading...");
     delay(5000);
}

void loop(){
  calibSensor();
  sensorValue = analogRead(moistReadpin);
  Serial.print(sensorValue);
  if(sensorValue > dryLimit) {
    Serial.println(" - time to water!");
    water();
  } else {
    Serial.println(" - ideal soil moisture.");
    digitalWrite(okLED, HIGH);
  }
  rest(); 
}

void calibSensor() {
  digitalWrite(moistPowerpin, HIGH);
  int calibTime = 4;
  while(calibTime != 0) {
    Serial.print("Calibrating... Approx. ");
    Serial.print(calibTime);
    Serial.println(" min left!");
    delay(60000);
    calibTime = calibTime - 1;
  }
}

void rest() {
  digitalWrite(okLED, LOW);
  digitalWrite(moistPowerpin, LOW);
  
  int timeWait = 10;
  while(timeWait != 0) {
    Serial.print("Next reading in ");
    Serial.print(timeWait);
    Serial.println(" minutes.");
    delay(60000);
    timeWait = timeWait - 1;
  }
}

void water(){
  digitalWrite(wateringLED, HIGH);
  digitalWrite(pumpPin, HIGH);
  delay(500);
  digitalWrite(pumpPin, LOW);
  digitalWrite(wateringLED, LOW);
}

void runTests() {
  //turns ON and OFF the LEDs in the circuit
  Serial.println("LED's test...");
  digitalWrite(wateringLED, HIGH);
  digitalWrite(okLED, HIGH);
  delay(2000);
  digitalWrite(wateringLED, LOW);
  digitalWrite(okLED, LOW);
  delay(2000);
  
  //turns ON and OFF the pump for a really short period
  Serial.println("Pump test...");
  digitalWrite(pumpPin, HIGH);
  delay(500);
  digitalWrite(pumpPin, LOW);
  delay(2000);
  
  //turns the moisture sensor ON and gives a sample reading to the Serial Monitor
  int testCounter = 0;
  digitalWrite(moistPowerpin, HIGH);
  Serial.println("Sensor test...");
  while (testCounter < 200) {
    sensorValue = analogRead(moistReadpin);
    Serial.println("Sensor value: ");
    Serial.print(sensorValue);
    Serial.println();
    testCounter = testCounter + 1;
    }
  digitalWrite(moistPowerpin, LOW);
  delay(2000);
}
