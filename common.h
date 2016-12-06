/*
 * Copyright 2013-2014 Mike Stirling
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of the Tiny Home Area Network stack.
 *
 * http://www.tinyhan.co.uk/
 *
 * common.h
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <Arduino.h>
#include <stdio.h>

#define __BSIZE 256
typedef unsigned int boolean_t;
static char __buf[__BSIZE];

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define DUMP(buf, size)

#define TRACE(...)                         \
  do {                                     \
    snprintf(__buf, __BSIZE, __VA_ARGS__); \
    Serial.print("T: ");                   \
    Serial.print(__buf);                   \
  } while (0)

#define INFO(...)                          \
  do {                                     \
    snprintf(__buf, __BSIZE, __VA_ARGS__); \
    Serial.print("I: ");                   \
    Serial.print(__buf);                   \
  } while (0)

#define ERROR(...)                         \
  do {                                     \
    snprintf(__buf, __BSIZE, __VA_ARGS__); \
    Serial.print("E: ");                   \
    Serial.print(__buf);                   \
  } while (0)

#define COMM(...)                          \
  do {                                     \
    snprintf(__buf, __BSIZE, __VA_ARGS__); \
    Serial.print(">");                     \
    Serial.print(__buf);                   \
  } while (0)

#define TRACE(...)
//#define INFO(...)
//#define ERROR(...)

#define FUNCTION_TRACE

#define PACKED			__attribute__((packed))
#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

#endif /* COMMON_H_ */
