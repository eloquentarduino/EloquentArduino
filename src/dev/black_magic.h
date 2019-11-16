#pragma once

#define CAT(a,b) a ## b
#define FIRST(a, ...) a
#define SECOND(a, b, ...) b
#define PROBE() ~, 1
#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define _NOT_0 PROBE()
#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define BOOL(x) NOT(NOT(x))
#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE
#define _IF_ELSE(condition) CAT(_IF_, condition)
#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))

#define EMPTY()
#define EVAL1(...) __VA_ARGS__
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL(...) EVAL1024(__VA_ARGS__)
#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()
#define _END_OF_ARGUMENTS_() 0
#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())

#define MAP(mapper, first, ...)           \
  mapper(first)  ;                         \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP)()(mapper, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#define MAP_WITH_ARG(mapper, arg, first, ...)           \
  mapper(arg, first)  ;                         \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP_WITH_ARG)()(mapper, arg, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP_WITH_ARG() MAP_WITH_ARG