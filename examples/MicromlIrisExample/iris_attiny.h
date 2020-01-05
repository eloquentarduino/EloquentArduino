#pragma once
/**
 * Compute kernel between feature vector and support vector.
 * Kernel type: poly
 */
double compute_kernel(double x[4], double w[4]) {
    double kernel = 0.0;
    for (uint16_t i = 0; i < 4; i++)
        kernel += x[i] *  w[i] ;
    kernel = pow((0.1 * kernel) + 0.0, 2);
    return kernel;
}
/**
 * Predict class for features vector
 */
int predict(double *x) {
    double kernels[24] = { 0 };
    double decisions[6] = { 0 };
    int votes[3] = { 0 };
    w[0] = 5.1;  w[1] = 3.3;  w[2] = 1.7;  w[3] = 0.5;
    kernels[0] = compute_kernel(x, w);
    w[0] = 4.8;  w[1] = 3.4;  w[2] = 1.9;  w[3] = 0.2;
    kernels[1] = compute_kernel(x, w);
    w[0] = 4.5;  w[1] = 2.3;  w[2] = 1.3;  w[3] = 0.3;
    kernels[2] = compute_kernel(x, w);
    w[0] = 5.1;  w[1] = 3.8;  w[2] = 1.9;  w[3] = 0.4;
    kernels[3] = compute_kernel(x, w);
    w[0] = 6.9;  w[1] = 3.1;  w[2] = 4.9;  w[3] = 1.5;
    kernels[4] = compute_kernel(x, w);
    w[0] = 6.3;  w[1] = 3.3;  w[2] = 4.7;  w[3] = 1.6;
    kernels[5] = compute_kernel(x, w);
    w[0] = 6.1;  w[1] = 2.9;  w[2] = 4.7;  w[3] = 1.4;
    kernels[6] = compute_kernel(x, w);
    w[0] = 5.6;  w[1] = 3.0;  w[2] = 4.5;  w[3] = 1.5;
    kernels[7] = compute_kernel(x, w);
    w[0] = 6.2;  w[1] = 2.2;  w[2] = 4.5;  w[3] = 1.5;
    kernels[8] = compute_kernel(x, w);
    w[0] = 5.9;  w[1] = 3.2;  w[2] = 4.8;  w[3] = 1.8;
    kernels[9] = compute_kernel(x, w);
    w[0] = 6.3;  w[1] = 2.5;  w[2] = 4.9;  w[3] = 1.5;
    kernels[10] = compute_kernel(x, w);
    w[0] = 6.7;  w[1] = 3.0;  w[2] = 5.0;  w[3] = 1.7;
    kernels[11] = compute_kernel(x, w);
    w[0] = 6.0;  w[1] = 2.7;  w[2] = 5.1;  w[3] = 1.6;
    kernels[12] = compute_kernel(x, w);
    w[0] = 5.4;  w[1] = 3.0;  w[2] = 4.5;  w[3] = 1.5;
    kernels[13] = compute_kernel(x, w);
    w[0] = 5.1;  w[1] = 2.5;  w[2] = 3.0;  w[3] = 1.1;
    kernels[14] = compute_kernel(x, w);
    w[0] = 4.9;  w[1] = 2.5;  w[2] = 4.5;  w[3] = 1.7;
    kernels[15] = compute_kernel(x, w);
    w[0] = 6.5;  w[1] = 3.2;  w[2] = 5.1;  w[3] = 2.0;
    kernels[16] = compute_kernel(x, w);
    w[0] = 6.0;  w[1] = 2.2;  w[2] = 5.0;  w[3] = 1.5;
    kernels[17] = compute_kernel(x, w);
    w[0] = 6.3;  w[1] = 2.7;  w[2] = 4.9;  w[3] = 1.8;
    kernels[18] = compute_kernel(x, w);
    w[0] = 6.2;  w[1] = 2.8;  w[2] = 4.8;  w[3] = 1.8;
    kernels[19] = compute_kernel(x, w);
    w[0] = 6.1;  w[1] = 3.0;  w[2] = 4.9;  w[3] = 1.8;
    kernels[20] = compute_kernel(x, w);
    w[0] = 6.3;  w[1] = 2.8;  w[2] = 5.1;  w[3] = 1.5;
    kernels[21] = compute_kernel(x, w);
    w[0] = 6.0;  w[1] = 3.0;  w[2] = 4.8;  w[3] = 1.8;
    kernels[22] = compute_kernel(x, w);
    w[0] = 5.9;  w[1] = 3.0;  w[2] = 5.1;  w[3] = 1.8;
    kernels[23] = compute_kernel(x, w);
    decisions[0] = 1.2231940660542209
                   + kernels[0] * 0.8459188923557006
                   + kernels[2] * 0.06103242244039368
                   + kernels[14] * -0.9069513147960943
            ;
    decisions[1] = 1.3037719678648867
                   + kernels[0] * 0.05756248848540525
                   + kernels[1] * 0.10628874990377811
                   + kernels[3] * 0.043958115616874335
                   + kernels[15] * -0.20780935400605768
            ;
    decisions[2] = 4.836163965115313
                   + kernels[4] * 0.4920190390355326
                   + kernels[5]
                   + kernels[6] * 0.5079809609644675
                   + kernels[7]
                   + kernels[8]
                   + kernels[9]
                   + kernels[10]
                   + kernels[11]
                   + kernels[12]
                   + kernels[13]
                   - kernels[15]
                   - kernels[16]
                   - kernels[17]
                   - kernels[18]
                   - kernels[19]
                   - kernels[20]
                   - kernels[21]
                   - kernels[22]
                   - kernels[23]
            ;
    votes[decisions[0] > 0 ? 0 : 1] += 1;
    votes[decisions[1] > 0 ? 0 : 2] += 1;
    votes[decisions[2] > 0 ? 1 : 2] += 1;
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