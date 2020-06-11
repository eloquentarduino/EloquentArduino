#include "imu_6050.h"
#include "pca.h"
#include "model.h"

#define NUM_SAMPLES 30
#define NUM_AXES 3
#define TRUNCATE 20
#define ACCEL_THRESHOLD 5
#define INTERVAL 30

float baseline[NUM_AXES];
float features[NUM_SAMPLES * NUM_AXES];
Eloquent::ML::Port::PCA pca;
Eloquent::ML::Port::SVM clf;


void setup() {
    Serial.begin(115200);
    imu_setup();
    calibrate();
}

void loop() {
    float ax, ay, az;

    imu_read(&ax, &ay, &az);

    ax = constrain(ax - baseline[0], -TRUNCATE, TRUNCATE);
    ay = constrain(ay - baseline[1], -TRUNCATE, TRUNCATE);
    az = constrain(az - baseline[2], -TRUNCATE, TRUNCATE);

    if (!motionDetected(ax, ay, az)) {
        delay(10);
        return;
    }

    recordIMU();
    printFeatures();
    // un-comment to run classification
    classify();
    delay(2000);
}

/**
 * "Zero" the readings
 */
void calibrate() {
    float ax, ay, az;

    for (int i = 0; i < 10; i++) {
        imu_read(&ax, &ay, &az);
        delay(100);
    }

    baseline[0] = ax;
    baseline[1] = ay;
    baseline[2] = az;
}

/**
 * Detect if motion is happening
 * @return
 */
bool motionDetected(float ax, float ay, float az) {
    return (abs(ax) + abs(ay) + abs(az)) > ACCEL_THRESHOLD;
}

/**
 * Fill the feature vector
 */
void recordIMU() {
    float ax, ay, az;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        imu_read(&ax, &ay, &az);

        ax = constrain(ax - baseline[0], -TRUNCATE, TRUNCATE);
        ay = constrain(ay - baseline[1], -TRUNCATE, TRUNCATE);
        az = constrain(az - baseline[2], -TRUNCATE, TRUNCATE);

        features[i * NUM_AXES + 0] = ax;
        features[i * NUM_AXES + 1] = ay;
        features[i * NUM_AXES + 2] = az;

        delay(INTERVAL);
    }
}

/**
 * Dump the feature vector to Serial monitor
 */
void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(float);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}

/**
 *
 */
void classify() {
    pca.transform(features);
    Serial.print("Detected gesture: ");
    Serial.println(clf.predictLabel(features));
}