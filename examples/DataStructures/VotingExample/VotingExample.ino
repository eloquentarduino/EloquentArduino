#include <ArduinoUnit.h>
#include <EloquentArduino.h>
#include <eloquentarduino/data_structures/Voting.h>


using namespace Eloquent::DataStructures;


test(not_enough_votes) {
    Voting<5> voting;

    voting.vote(1);

    assertFalse(voting.agree(0.5));
}

test(no_quorum) {
    Voting<3> voting;

    voting.vote(1);
    voting.vote(2);
    voting.vote(3);

    assertFalse(voting.agree(2));
    assertFalse(voting.agree(0.5));
}

test(absolute_quorum) {
    Voting<3> voting;

    voting.vote(1);
    voting.vote(1);
    voting.vote(2);

    assertTrue(voting.agree(2));
    assertEqual(voting.decision(), 1);
}

test(relative_quorum) {
    Voting<3> voting;

    voting.vote(1);
    voting.vote(1);
    voting.vote(2);

    assertTrue(voting.agree(0.5));
    assertEqual(voting.decision(), 1);
}

test(rolling_votes) {
    Voting<3> voting;

    voting.vote(1);
    voting.vote(1);
    voting.vote(2);
    voting.vote(2);
    voting.vote(3);

    assertTrue(voting.agree(2));
    assertEqual(voting.decision(), 2);
}

void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}