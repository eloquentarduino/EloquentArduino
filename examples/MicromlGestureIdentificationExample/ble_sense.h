#include <Arduino_LSM9DS1.h>


void imu_setup() {
    IMU.begin();
}

void imu_read(float *ax, float *ay, float *az) {
    if (IMU.accelerationAvailable())
        IMU.readAcceleration(*ax, *ay, *az);
}