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

// OTHER
unsigned long time_last_temperature_update = 0;


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

void update_temperature(){
  // Get and update temperature

  // Sensor is a TMP36
  // https://www.arduino.cc/en/uploads/Main/TemperatureSensor.pdf
  int sensorVal = analogRead(temperatureSensorPin);
  float voltage = (sensorVal/1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  float avgTemp = calculateMeanTemperature(temperature);
  servoAngle = map(avgTemp, 15, 35, 0, 179);
  servo.write(servoAngle);

  // Loging
  Serial.print(" Sensor Value: ");
  Serial.print(sensorVal);
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", degreees C: ");
  Serial.print(temperature);
  Serial.print(", avg(degreees) C: ");
  Serial.print(avgTemp);
  Serial.print(", angle: ");
  Serial.println(servoAngle);
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
  unsigned long current_time = millis();

  if(current_time >= time_last_temperature_update + 1000){
    time_last_temperature_update = current_time;
    Serial.print("Current Run Time: ");
    Serial.print(current_time);

    update_temperature();
  }
}