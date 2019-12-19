#include <Wire.h>
// library from https://github.com/bolderflight/MPU9250
#include <MPU9250.h>

MPU9250 imu(Wire, 0x68);

void imu_setup() {
    Wire.begin();
    imu.begin();
}

void imu_read(float *ax, float *ay, float *az) {
    imu.readSensor();

    *ax = imu.getAccelX_mss();
    *ay = imu.getAccelY_mss();
    *az = imu.getAccelZ_mss();
}