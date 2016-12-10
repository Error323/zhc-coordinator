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
 * board.h
 *
 * Simple sensor example, board definition header
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

/* Pin definitions */
#define TRX_SDN 7
#define nTRX_SEL 10

#define nTRX_IRQ 6
#define LED LED_BUILTIN

/*! Return the current value of the named IO port */
#define INP(id) digitalRead(id)
/*! Sets the named IO port to the specified value */
#define OUTP(id, val) digitalWrite(id, val)
/*! Turns on the named IO port */
#define SETP(id) digitalWrite(id, HIGH)
/*! Turns off the named IO port */
#define CLEARP(id) digitalWrite(id, LOW)

#define TRX_OFF() SETP(TRX_SDN)
#define TRX_ON() CLEARP(TRX_SDN)

#endif /*BOARD_H_*/
