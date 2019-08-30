---
title: Finite State Machine - Macros
---

[Finite State Machines](https://en.wikipedia.org/wiki/Finite-state_machine), in the Arduino
 context, are a formal rapresentation of the lifecycle of your project.
 You define `states` your code will be in, each with a specific task.
 This will help you clearly isolate atomic pieces of functionality and properly organizing them,
 avoiding the spaghetti code trap.

I was looking for a good example of FSM for Arduino, but since I couldn't find one, I'll report
the code of a project I'm working on. In short, I read some sensors and send them over Sigfox network.
(only the relevant code is reported)

```
#define BINARY_STATES 1
#include <eMacroFSM.h>

#define STATE_WARMUP 1
#define STATE_SENSE 2
#define STATE_SENSE_FAIL 4
#define STATE_SIGFOX 8
#define STATE_SIGFOX_FAIL 16
#define STATE_DOWN 32

...

void loop() {
  in_state(STATE_WARMUP) {
    staying {
      Serial.println("warming sensors up");
      led.turnOn();
      mosfet.turnOn();
      delay(WARMUP_TIME);
      set_state(STATE_SENSE);
    }
  }

  in_state(STATE_SENSE) {
    staying {
      sense.siT = siT.readValue();
      sense.siH = siH.readValue();
      sense.lwd = 15 - constrain(touchRead(LWD), 0, 15);
      // @todo
    }
  }

  in_state(STATE_SENSE_FAIL) {
    Serial.println("Sensing failed");

    staying {
      if (sense_retries == 0) {
        set_state(STATE_DOWN);
      }
      else {
        sense_retries--;
        mosfet.turnOff();
        delay(5000);
        set_state(STATE_WARMUP);
      }
    }
  }

  in_state(STATE_SIGFOX) {
    staying {
      // @todo
    }
  }

  in_state(STATE_SIGFOX_FAIL) {
    staying {
      if (sigfox_retries == 0) {
        set_state(STATE_DOWN);
      }
      else {
        sigfox_retries--;
        mosfet.turnOff();
        delay(5000);
        set_state(STATE_SIGFOX);
      }
    }
  }

  in_state(STATE_DOWN) {
    staying {
      Serial.println("down");
      led.turnOff();
      mosfet.turnOff();
      delay(1000);
      ESP.deepSleep(1000L * 1000 * 60 * SLEEP_MINUTES);
    }
  }
}
```