#pragma once

uint32_t __fsm;
uint32_t __fsmprev;
uint32_t __fsmscope;
uint32_t __fsmscheduled;


// use binary & or strict equality to check states
#ifdef BINARY_STATES
#define STATE_EQ &
#else
#define STATE_EQ ==
#endif

#define _STATE_EQ_ (__fsm STATE_EQ __fsmscope)

// execute block when in given state
#define in_state(state) if ((__fsm STATE_EQ state || __fsmprev STATE_EQ state) && (__fsmscope = state))

// execute block when staying in current state
#define staying if (_STATE_EQ_ && (__fsm STATE_EQ __fsmprev))

// execute block when entering to current state
#define entering if (_STATE_EQ_ && __fsm != __fsmprev)

// execute block when leaving to current state
#define leaving if ((__fsmprev STATE_EQ __fsmscope) && (__fsm != __fsmprev))

// execute block when coming from a given state
#define coming_from(state) if (_STATE_EQ_ && __fsmprev STATE_EQ state)

// execute block when leaving to a given state
#define leaving_to(state) if ((__fsmprev STATE_EQ __fsmscope) && (__fsm STATE_EQ state))

// update state
#define set_state(state) __fsmprev = __fsm, __fsm = state

// schedule state update
#define schedule_state(state) __fsmscheduled = state

// apply scheduled state
#define commit_state set_state(__fsmscheduled ? __fsmscheduled : __fsm), __fsmscheduled = 0