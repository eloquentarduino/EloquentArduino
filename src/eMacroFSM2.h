#pragma once

typedef uint32_t State;
typedef uint32_t Event;

#define start_state(state) if (current_state == 0) current_state = state;

#define in_state(state) if (state == current_state && !scheduled_state)

#define entering(state) if (state == scheduled_state)

#define entering_from(state, from) if (state == scheduled_state && from == current_state)

#define leaving(state) if (state == current_state && scheduled_state)

#define leaving_to(state, to) if (state == current_state && to == scheduled_state)

#define trigger_transition(event) scheduled_event = event;
#define trigger_transition_if(condition, event) if (condition) scheduled_event = event;
#define trigger_ifelse(condition, event_ok, event_fail) scheduled_event = (condition) ? event_ok : event_fail;

#define transit(from, e, to) if (current == from && event == e) return to;

#define transit_if(from, e, condition, to) if (current == from && event == e) if (condition) return to;

#define transit_ifelse(from, e, condition, to_true, to_false) if (current == from && event == e) return (condition) ? to_true : to_false;

#ifdef ELOQUENT_FSM
#define being_in if (current ==
#define getting && event ==
#define go_to ) return
#endif


#define loop_fsm() \
    static State current_state; \
    static State scheduled_state; \
    static Event scheduled_event; \
\
    if (scheduled_event) { \
        scheduled_state = transition_function(current_state, scheduled_event); \
        scheduled_event = 0; \
    } else if (scheduled_state) { \
        current_state = scheduled_state; \
        scheduled_state = 0; \
    }