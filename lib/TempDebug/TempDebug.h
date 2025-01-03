/*
 * Copyright (c) 2024 Boonyakorn Thanpanit
 */

#ifndef LIB_TEMPDEBUG_TEMPDEBUG_H_
#define LIB_TEMPDEBUG_TEMPDEBUG_H_

#ifdef DEBUG
#define debug1(x) Serial.print(x)
#define debugln1(x) Serial.println(x)
#define debug2(x, y) Serial.print(x, y)
#define debugln2(x, y) Serial.println(x, y)
#define GET_MACRO(_1, _2, NAME, ...) NAME
#define debug(...) GET_MACRO(__VA_ARGS__, debug2, debug1)(__VA_ARGS__)
#define debugln(...) GET_MACRO(__VA_ARGS__, debugln2, debugln1)(__VA_ARGS__)
#else
#define debug1(x)
#define debugln1(x)
#define debug2(x, y)
#define debugln2(x, y)
#define GET_MACRO(_1, _2, NAME, ...) NAME
#define debug(...) GET_MACRO(__VA_ARGS__, debug2, debug1)(__VA_ARGS__)
#define debugln(...) GET_MACRO(__VA_ARGS__, debugln2, debugln1)(__VA_ARGS__)
#endif

#endif  // LIB_TEMPDEBUG_TEMPDEBUG_H_
