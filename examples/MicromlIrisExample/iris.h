#pragma once
/**
 * Compute kernel between feature vector and support vector.
 * Kernel type: linear
 */
double compute_kernel(double x[4], ...) {
    va_list w;
    double kernel = 0.0;
    va_start(w, 4);
    for (uint16_t i = 0; i < 4; i++)
        kernel += x[i] * va_arg(w, double);
    return kernel;
}
/**
 * Predict class for features vector
 */
int predict(double *x) {
    double kernels[15] = { 0 };
    double decisions[6] = { 0 };
    int votes[3] = { 0 };
    kernels[0] = compute_kernel(x,   6.9  , 3.1  , 4.9  , 1.5 );
    kernels[1] = compute_kernel(x,   5.7  , 2.8  , 4.5  , 1.3 );
    kernels[2] = compute_kernel(x,   6.3  , 3.3  , 4.7  , 1.6 );
    kernels[3] = compute_kernel(x,   4.9  , 2.4  , 3.3  , 1.0 );
    kernels[4] = compute_kernel(x,   6.1  , 2.9  , 4.7  , 1.4 );
    kernels[5] = compute_kernel(x,   5.6  , 3.0  , 4.5  , 1.5 );
    kernels[6] = compute_kernel(x,   6.2  , 2.2  , 4.5  , 1.5 );
    kernels[7] = compute_kernel(x,   4.9  , 2.5  , 4.5  , 1.7 );
    kernels[8] = compute_kernel(x,   6.5  , 3.2  , 5.1  , 2.0 );
    kernels[9] = compute_kernel(x,   6.4  , 2.7  , 5.3  , 1.9 );
    kernels[10] = compute_kernel(x,   6.5  , 3.0  , 5.5  , 1.8 );
    kernels[11] = compute_kernel(x,   6.0  , 2.2  , 5.0  , 1.5 );
    kernels[12] = compute_kernel(x,   4.6  , 3.1  , 1.5  , 0.2 );
    kernels[13] = compute_kernel(x,   5.4  , 3.9  , 1.7  , 0.4 );
    kernels[14] = compute_kernel(x,   5.7  , 3.8  , 1.7  , 0.3 );
    decisions[0] = 5.649189842276587
                   + kernels[0] * 0.8695514658046984
                   + kernels[1] * 0.06616679955553174
                   + kernels[2] * 0.8527543868372957
                   + kernels[4]
                   + kernels[5]
                   + kernels[6]
                   - kernels[7]
                   - kernels[8]
                   + kernels[9] * -0.7884726521975259
                   - kernels[10]
                   - kernels[11]
            ;
    decisions[1] = -1.3924837643789074
                   + kernels[3] * 0.45296487164978
                   + kernels[12] * -0.38073987478736276
                   + kernels[14] * -0.07222499686241728
            ;
    decisions[2] = -1.2054358490148886
                   + kernels[7] * 0.1757465517828809
                   + kernels[12] * -0.09054230566349034
                   + kernels[13] * -0.08520424611939055
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
/**
 * Convert class idx to readable name
 */
const char* classIdxToName(uint8_t classIdx) {
    switch (classIdx) {
        case 0:
            return "versicolor";
        case 1:
            return "virginica";
        case 2:
            return "setosa";
        default:
            return "UNKNOWN";
    }
}
