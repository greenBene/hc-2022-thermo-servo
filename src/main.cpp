#include <Arduino.h>
#include <Servo.h>

// SERVO variables
Servo servo;
int servoAngle = 0;
int sensorVal;

// TEMPERATURE  variables
int const temperatureSensorPin = A0;
float temperatureArray[10];
int currentTemperatureIndex = 0;


float calculateMeanTemperature(float temperature) {
  temperatureArray[currentTemperatureIndex] = temperature;
  currentTemperatureIndex = (currentTemperatureIndex + 1) % 10;
  float mean_temperature = 0;
  for (int i = 0; i < 10; i++) {
    mean_temperature += temperatureArray[i];
  }
  mean_temperature /= 10.0;
  return mean_temperature;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Good morning! =)");

  servo.attach(9);

  for (int i = 0; i < 10; i++) {
    temperatureArray[i] = 15.0;
  }
}

void loop() {
  millis();
  int sensorVal = analogRead(temperatureSensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - 0.5) * 100;
  Serial.print(", degreees C: ");
  Serial.print(temperature);

  float avgTemp = calculateMeanTemperature(temperature);
  Serial.print(", avg(degreees) C: ");
  Serial.print(avgTemp);
  
  servoAngle = map(avgTemp, 15, 35, 0, 179);
  Serial.print(", angle: ");
  Serial.println(servoAngle);
  servo.write(servoAngle);
  delay(1000);
}