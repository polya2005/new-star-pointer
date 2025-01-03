/*
 * Copyright (c) 2024 Boonyakorn Thanpanit

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
