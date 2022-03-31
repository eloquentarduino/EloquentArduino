#include <ArduinoUnit.h>
#include <EloquentArduino.h>
#include <eloquentarduino/data_structures/LongShortTermVoting.h>


using namespace Eloquent::DataStructures;


test(not_enough_votes) {
    LongShortTermVoting<3, 3> voting(2, 2);

    voting.vote(1);

    assertFalse(voting.agree());
}

test(no_short_term_quorum) {
    LongShortTermVoting<3, 3> voting(2, 2);

    voting.vote(1);
    voting.vote(2);
    voting.vote(3);

    assertFalse(voting.agree());
}

test(no_long_term_quorum) {
    LongShortTermVoting<3, 3> voting(2, 2);

    voting.vote(1);
    voting.vote(1);
    voting.vote(2);

    assertFalse(voting.agree());
}

test(quorum) {
    LongShortTermVoting<3, 3> voting(2, 2);

    // 1st long term vote
    voting.vote(1);
    voting.vote(1);
    voting.vote(2);
    // 2nd long term vote
    // now votes become [1, 2, 1]
    voting.vote(1);
    // 3rd long term voting
    // now votes become [2, 1, 1]
    voting.vote(1);

    assertTrue(voting.agree());
    assertEqual(voting.decision(), 1);
}


void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}