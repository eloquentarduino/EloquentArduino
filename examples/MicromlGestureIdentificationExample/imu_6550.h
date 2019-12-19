#include <Wire.h>
// library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include <MPU6050.h>
#define OUTPUT_READABLE_ACCELGYRO

MPU6050 imu;

void imu_setup() {
    Wire.begin();
    imu.initialize();
}

void imu_read(float *ax, float *ay, float *az) {
    float gx, gy, gz;

    imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}