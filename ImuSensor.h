#ifndef IMU_HPP
#define IMU_HPP

class ImuSensor {
public:
    void init();

    float get_yaw();
    float get_roll();
    float get_pitch();

    void calibrateImu(int delayMillis, int calibrationMillis);
    void doCalculations();
    void processImu();
    bool readImu();
private:
    float accelX,            accelY,             accelZ,            // units m/s/s i.e. accelZ if often 9.8 (gravity)
          gyroX,             gyroY,              gyroZ,             // units dps (degrees per second)
          gyroDriftX,        gyroDriftY,         gyroDriftZ,        // units dps
          gyroRoll,          gyroPitch,          gyroYaw,           // units degrees (expect major drift)
          gyroCorrectedRoll, gyroCorrectedPitch, gyroCorrectedYaw,  // units degrees (expect minor drift)
          accRoll,           accPitch,           accYaw,            // units degrees (roll and pitch noisy, yaw not possible)
          complementaryRoll, complementaryPitch, complementaryYaw;  // units degrees (excellent roll, pitch, yaw minor drift)

    long lastTime;
    long lastInterval;
};

#endif // IMU_HPP