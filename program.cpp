#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_TSL2591.h>

Adafruit_BME280 bme;
Adafruit_TSL2591 tsl;

const int moisturePin = A0;
const int phPin = A1;
const int pressurePin = A2;
const int gasPin = A3;

unsigned long startTime;
unsigned long elapsedTime;

void setup() {
  Serial.begin(9600);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  if (!tsl.begin()) {
    Serial.println("Could not find a valid TSL2591 sensor, check wiring!");
    while (1);
  }

  startTime = millis(); // Record the start time
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  uint16_t light = tsl.getFullLuminosity();
  
  int moistureLevel = analogRead(moisturePin);
  int phValue = analogRead(phPin);
  int pressureValue = analogRead(pressurePin);
  int gasValue = analogRead(gasPin);

  // Calculate elapsed time
  elapsedTime = millis() - startTime;

  // Process the data and print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Light Level: ");
  Serial.println(light);

  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  Serial.print("pH Value: ");
  Serial.println(phValue);

  Serial.print("Pressure Sensor Value: ");
  Serial.println(pressureValue);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Estimate time for wound healing based on sensor data (example calculation)
  float healingFactor = 0.0001; // Adjust based on your algorithm
  int estimatedHealingTime = int(healingFactor * (moistureLevel + phValue + pressureValue + gasValue) * elapsedTime);

  Serial.print("Elapsed Time: ");
  Serial.print(elapsedTime / (1000 * 60 * 60)); // Convert to hours
  Serial.println(" hours");

  Serial.print("Estimated Time to Heal: ");
  Serial.print(estimatedHealingTime / (1000 * 60 * 60)); // Convert to hours
  Serial.println(" hours");

  // Add your logic for analyzing the data and determining wound condition here

  delay(5000);
}
