/**
 * @author Simone Salerno <web@agrimag.it>
 * @date 2019-08-30
 *
 * This is a toy example of the port of a SVM trained in scikit-learn
 * to C code classifying the IRIS dataset.
 * It is meant for extremely low memory hardware; it sacrifices program space
 * to achieve a memory footprint of a few bytes.
 * This is useful with classic Arduino boards (UNO, Nano) which have 32kb of flash
 * and 2kb of RAM.
 *
 * https://github.com/nok/sklearn-porter is a mature project in the same vain,
 * if you need one.
 * I looked at their output code to fix a bug in my implementation.
 * Their approach, however, is not memory-efficient, since it stores all
 * support vectors in memory.
 */

#define DATASET_SIZE 30
double dataset[30][4] = {{6.7,3.1,5.6,2.4},{6.2,3.4,5.4,2.3},{6.1,2.8,4.7,1.2},{6.5,3.2,5.1,2.0},{5.5,2.4,3.7,1.0},{5.5,2.4,3.8,1.1},{7.1,3.0,5.9,2.1},{6.5,2.8,4.6,1.5},{4.9,3.0,1.4,0.2},{5.8,2.7,3.9,1.2},{6.0,3.0,4.8,1.8},{6.3,2.8,5.1,1.5},{5.7,4.4,1.5,0.4},{4.6,3.1,1.5,0.2},{6.1,2.9,4.7,1.4},{7.3,2.9,6.3,1.8},{4.4,3.0,1.3,0.2},{5.7,2.9,4.2,1.3},{6.9,3.1,5.1,2.3},{4.9,3.1,1.5,0.1},{5.8,4.0,1.2,0.2},{6.7,2.5,5.8,1.8},{4.9,3.6,1.4,0.1},{5.1,3.7,1.5,0.4},{5.0,2.3,3.3,1.0},{6.3,2.9,5.6,1.8},{4.7,3.2,1.6,0.2},{5.7,2.6,3.5,1.0},{7.7,3.8,6.7,2.2},{6.3,2.7,4.9,1.8}};
// expected output 2 2 1 2 1 1 2 1 0 1 2 2 0 0 1 2 0 1 2 0 0 2 0 0 1 2 0 1 2 2


double kernels[27];
double decisions[3];
int    votes[3];


double apply_kernel(double v);
double dot(double *x, float *w, uint8_t len);
int    predict(double *x);


void setup() {
    Serial.begin(115200);
    delay(1000);

    for (uint8_t i = 0; i < DATASET_SIZE; i++)
        Serial.println(predict(dataset[i]));
}

void loop() {
    delay(10000);
}

/**
 * This is meant for kernels different than linear
 * @not-implement
 */
double apply_kernel(double v) { return v; }

/**
 * Dot product
 */
double dot(double *x, float *w, uint8_t len) {
    double dot = 0;

    for (int i = 0; i < len; i++)
        dot += x[i] * w[i];

    return dot;
}

/**
 * SVM classification
 */
int predict(double *x) {
    float w[27];

    // reset variables
    for (uint8_t i = 0; i < 27; i++) kernels[i] = 0;
    for (uint8_t i = 0; i < 3; i++) decisions[i] = votes[i] = 0;

    // compute kernels values
    w[0] = 4.800000; w[1] = 3.400000; w[2] = 1.900000; w[3] = 0.200000;
    kernels[0] = apply_kernel(dot(x, w, 4));
    w[0] = 4.500000; w[1] = 2.300000; w[2] = 1.300000; w[3] = 0.300000;
    kernels[1] = apply_kernel(dot(x, w, 4));
    w[0] = 5.100000; w[1] = 3.300000; w[2] = 1.700000; w[3] = 0.500000;
    kernels[2] = apply_kernel(dot(x, w, 4));
    w[0] = 6.300000; w[1] = 2.500000; w[2] = 4.900000; w[3] = 1.500000;
    kernels[3] = apply_kernel(dot(x, w, 4));
    w[0] = 6.000000; w[1] = 2.700000; w[2] = 5.100000; w[3] = 1.600000;
    kernels[4] = apply_kernel(dot(x, w, 4));
    w[0] = 5.100000; w[1] = 2.500000; w[2] = 3.000000; w[3] = 1.100000;
    kernels[5] = apply_kernel(dot(x, w, 4));
    w[0] = 6.900000; w[1] = 3.100000; w[2] = 4.900000; w[3] = 1.500000;
    kernels[6] = apply_kernel(dot(x, w, 4));
    w[0] = 6.700000; w[1] = 3.000000; w[2] = 5.000000; w[3] = 1.700000;
    kernels[7] = apply_kernel(dot(x, w, 4));
    w[0] = 6.300000; w[1] = 3.300000; w[2] = 4.700000; w[3] = 1.600000;
    kernels[8] = apply_kernel(dot(x, w, 4));
    w[0] = 5.900000; w[1] = 3.200000; w[2] = 4.800000; w[3] = 1.800000;
    kernels[9] = apply_kernel(dot(x, w, 4));
    w[0] = 5.400000; w[1] = 3.000000; w[2] = 4.500000; w[3] = 1.500000;
    kernels[10] = apply_kernel(dot(x, w, 4));
    w[0] = 5.600000; w[1] = 3.000000; w[2] = 4.500000; w[3] = 1.500000;
    kernels[11] = apply_kernel(dot(x, w, 4));
    w[0] = 6.200000; w[1] = 2.200000; w[2] = 4.500000; w[3] = 1.500000;
    kernels[12] = apply_kernel(dot(x, w, 4));
    w[0] = 6.100000; w[1] = 2.900000; w[2] = 4.700000; w[3] = 1.400000;
    kernels[13] = apply_kernel(dot(x, w, 4));
    w[0] = 6.800000; w[1] = 2.800000; w[2] = 4.800000; w[3] = 1.400000;
    kernels[14] = apply_kernel(dot(x, w, 4));
    w[0] = 6.300000; w[1] = 2.500000; w[2] = 5.000000; w[3] = 1.900000;
    kernels[15] = apply_kernel(dot(x, w, 4));
    w[0] = 6.000000; w[1] = 2.200000; w[2] = 5.000000; w[3] = 1.500000;
    kernels[16] = apply_kernel(dot(x, w, 4));
    w[0] = 6.500000; w[1] = 3.000000; w[2] = 5.200000; w[3] = 2.000000;
    kernels[17] = apply_kernel(dot(x, w, 4));
    w[0] = 5.900000; w[1] = 3.000000; w[2] = 5.100000; w[3] = 1.800000;
    kernels[18] = apply_kernel(dot(x, w, 4));
    w[0] = 6.100000; w[1] = 3.000000; w[2] = 4.900000; w[3] = 1.800000;
    kernels[19] = apply_kernel(dot(x, w, 4));
    w[0] = 6.300000; w[1] = 2.700000; w[2] = 4.900000; w[3] = 1.800000;
    kernels[20] = apply_kernel(dot(x, w, 4));
    w[0] = 4.900000; w[1] = 2.500000; w[2] = 4.500000; w[3] = 1.700000;
    kernels[21] = apply_kernel(dot(x, w, 4));
    w[0] = 6.300000; w[1] = 2.800000; w[2] = 5.100000; w[3] = 1.500000;
    kernels[22] = apply_kernel(dot(x, w, 4));
    w[0] = 6.000000; w[1] = 3.000000; w[2] = 4.800000; w[3] = 1.800000;
    kernels[23] = apply_kernel(dot(x, w, 4));
    w[0] = 6.500000; w[1] = 3.200000; w[2] = 5.100000; w[3] = 2.000000;
    kernels[24] = apply_kernel(dot(x, w, 4));
    w[0] = 7.200000; w[1] = 3.000000; w[2] = 5.800000; w[3] = 1.600000;
    kernels[25] = apply_kernel(dot(x, w, 4));
    w[0] = 6.200000; w[1] = 2.800000; w[2] = 4.800000; w[3] = 1.800000;
    kernels[26] = apply_kernel(dot(x, w, 4));

    // vote
    decisions[0] = 1.452521 + kernels[5] * -0.747880 + kernels[1] * 0.077045 + kernels[2] * 0.670835;
    decisions[1] = 1.504690 + kernels[21] * -0.203636 + kernels[0] * 0.156740 + kernels[2] * 0.046896;
    decisions[2] = 6.784509 + kernels[15] * -0.645817 + kernels[16] * -1.000000 + kernels[17] * -0.160178 + kernels[18] * -1.000000 + kernels[19] * -1.000000 + kernels[20] * -1.000000 + kernels[21] * -1.000000 + kernels[22] * -1.000000 + kernels[23] * -1.000000 + kernels[24] * -1.000000 + kernels[25] * -0.438471 + kernels[26] * -1.000000 + kernels[3] * 1.000000 + kernels[4] * 1.000000 + kernels[6] * 1.000000 + kernels[7] * 1.000000 + kernels[8] * 1.000000 + kernels[9] * 1.000000 + kernels[10] * 1.000000 + kernels[11] * 1.000000 + kernels[12] * 1.000000 + kernels[13] * 1.000000 + kernels[14] * 0.244466;
    votes[decisions[0] > 0 ? 0 : 1] += 1;
    votes[decisions[1] > 0 ? 0 : 2] += 1;
    votes[decisions[2] > 0 ? 1 : 2] += 1;

    // classify
    int classVal = -1;
    int classIdx = -1;

    for (int i = 0; i < 3; i++) {
        if (votes[i] > classVal) {
            classVal = votes[i];
            classIdx = i;
        }
    }

    return classIdx;
}