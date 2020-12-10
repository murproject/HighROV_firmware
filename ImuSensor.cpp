/* За основу был взят следующий пример:
 * https://github.com/arduino-libraries/Arduino_LSM6DS3/pull/4
 */

#include "ImuSensor.h"
#include <Arduino_LSM6DS3.h>

void ImuSensor::init() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
  }

  calibrateImu(250, 250);
  lastTime = micros();

  complementaryYaw = 0;
  complementaryRoll = 0;
  complementaryPitch = 0;
}

void ImuSensor::calibrateImu(int delayMillis, int calibrationMillis) {
  int calibrationCount = 0;
  delay(delayMillis);

  float sumX, sumY, sumZ;
  int startTime = millis();
  while (millis() < startTime + calibrationMillis) {
    if (readImu()) {
      sumX += gyroX;
      sumY += gyroY;
      sumZ += gyroZ;
      calibrationCount++;
    }
  }

  if (calibrationCount == 0) {
    Serial.println("Failed to calibrate");
  }

  gyroDriftX = sumX / calibrationCount;
  gyroDriftY = sumY / calibrationCount;
  gyroDriftZ = sumZ / calibrationCount;
}

bool ImuSensor::readImu() {
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() ) {
    IMU.readAcceleration(accelX, accelY, accelZ);
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
    return true;
  }
  return false;
}

void ImuSensor::processImu() {
  if (readImu()) {
    long currentTime = micros();
    lastInterval = currentTime - lastTime;
    lastTime = currentTime;

    doCalculations();
  }
}

void ImuSensor::doCalculations() {
  accRoll = atan2(accelY, accelZ) * 180 / M_PI;
  accPitch = atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180 / M_PI;

  float lastFrequency = (float) 1000000.0 / lastInterval;
  gyroRoll = gyroRoll + (gyroX / lastFrequency);
  gyroPitch = gyroPitch + (gyroY / lastFrequency);
  gyroYaw = gyroYaw + (gyroZ / lastFrequency);

  gyroCorrectedRoll = gyroCorrectedRoll + ((gyroX - gyroDriftX) / lastFrequency);
  gyroCorrectedPitch = gyroCorrectedPitch + ((gyroY - gyroDriftY) / lastFrequency);
  gyroCorrectedYaw = gyroCorrectedYaw + ((gyroZ - gyroDriftZ) / lastFrequency);

  complementaryRoll = complementaryRoll + ((gyroX - gyroDriftX) / lastFrequency);
  complementaryPitch = complementaryPitch + ((gyroY - gyroDriftY) / lastFrequency);
  complementaryYaw = complementaryYaw + ((gyroZ - gyroDriftZ) / lastFrequency);

  complementaryRoll = 0.98 * complementaryRoll + 0.02 * accRoll;
  complementaryPitch = 0.98 * complementaryPitch + 0.02 * accPitch;
}

float ImuSensor::get_yaw() {
    return complementaryYaw;
}

float ImuSensor::get_pitch() {
    return complementaryPitch;
}

float ImuSensor::get_roll() {
    return complementaryRoll;
}
