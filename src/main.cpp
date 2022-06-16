#include <Arduino.h>
#include <Servo.h>

Servo myServo;
int const sensorPin = A0;
int angle = 0;
int sensorVal;

float tempArr[10];
int valueIndex = 0;


float calcAvgTemp(float temp) {
  tempArr[valueIndex] = temp;
  valueIndex = (valueIndex + 1) % 10;
  float avg_temp = 0;
  for (int i = 0; i < 10; i++) {
    avg_temp += tempArr[i];
  }
  avg_temp /= 10.0;
  return avg_temp;
}

void setup() {
  myServo.attach(9);
  Serial.begin(9600);

  for (int i = 0; i < 10; i++) {
    tempArr[i] = 15.0;
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - 0.5) * 100;
  Serial.print(", degreees C: ");
  Serial.print(temperature);

  float avgTemp = calcAvgTemp(temperature);
  Serial.print(", avg(degreees) C: ");
  Serial.print(avgTemp);
  
  angle = map(avgTemp, 15, 35, 0, 179);
  Serial.print(", angle: ");
  Serial.println(angle);
  myServo.write(angle);
  delay(1000);
}