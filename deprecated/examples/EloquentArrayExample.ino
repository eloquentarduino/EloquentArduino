#include <EloquentLogging.h>
#include <EloquentArray.h>

using namespace Eloquent;

int _numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
Array<int> numbers(10, _numbers);



void setup() {
    Serial.begin(9600);
    Serial.println("Array example");

    assert_equal("Array length should be 10", numbers.count(), 10);
    assert_equal("Array min should be 0", numbers.getMin(), 0);
    assert_equal("Array max should be 9", numbers.getMax(), 9);
    assert_equal("Array sum should be 45", numbers.getSum(), 45);

    // You can set an element's value
    numbers.put(0, 10);
    assert_equal("Array min should be 1", numbers.getMin(), 1);
    assert_equal("Array max should be 10", numbers.getMax(), 10);
    assert_equal("Array sum should be 55", numbers.getSum(), 55);

    // You can extract sub-parts of the array
    // first arument is the start index
    // second (optional) argument is the length
    numbers.slice(1);
    assert_equal("Array length should be 9", numbers.count(), 9);
    assert_equal("Array min should be 1", numbers.getMin(), 1);
    assert_equal("Array max should be 9", numbers.getMax(), 9);

    // Now array should be [1, 2, 3, 4, 5]
    numbers.slice(0, 5);
    assert_equal("Array length should be 5", numbers.count(), 5);
    assert_equal("Array min should be 1", numbers.getMin(), 1);
    assert_equal("Array max should be 5", numbers.getMax(), 5);

    // You can even slice from the end!
    numbers.slice(-3, 2);
    assert_equal("Array length should be 2", numbers.count(), 2);
    assert_equal("Array min should be 3", numbers.getMin(), 3);
    assert_equal("Array max should be 4", numbers.getMax(), 4);
    assert_equal("Array avg should be 3.5", numbers.getAvg(), 3.5);
}


void loop() {

}
