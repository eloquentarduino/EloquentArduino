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
    int16_t _ax, _ay, _az, _gx, _gy, _gz;

    imu.getMotion6(&_ax, &_ay, &_az, &_gx, &_gy, &_gz);

    *ax = _ax;
    *ay = _ay;
    *az = _az;
}
