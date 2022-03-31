#include <eIO.h>

using namespace Eloquent;
using namespace Eloquent::IO;


float arr[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
ArrayInputStream is(arr, sizeof(arr) / sizeof(float));


void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println();
    is
        .then(new Constrain(0, 9999))
        .then(new EWMA(0.7))
        .then(new Map(0, 10, 0, 100))
        .then(new Average(3))
        //.then(new Round(RoundStrategy::FLOOR))
    ;
}

void loop() {
    if (!isnan(is.read())) {
        Serial.print(is.raw());
        Serial.print('\t');
        Serial.println(is.value());
    }
}