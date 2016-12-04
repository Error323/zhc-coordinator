/*!
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
 * tinyhan_platform.h
 *
 * Example platform definitions for an ATMEGA328 based board
 *
 */

#ifndef TINYHAN_PLATFORM_H_
#define TINYHAN_PLATFORM_H_

/* Undefine debug for radio modules if we are using OTA syslog */
#undef DEBUG

#include <stdint.h>
#include <SPI.h>
#include "common.h"
#include "board.h"

/********************************/
/* BOARD SPECIFIC CONFIGURATION */
/********************************/

/*! Port definition for SPI select pin */
#define nSELECT			nTRX_SEL
/*! Port definition for interrupt pin */
#define nIRQ			nTRX_IRQ

/***********************************/
/* PLATFORM SPECIFIC CONFIGURATION */
/***********************************/

/*! Delay for specified number of ms */
#define DELAY_MS(a)		delay(a)

/*! Wait for a transceiver interrupt (may be empty for
 * platforms which rely on polling)
 */
#define WAIT_EVENT()

/*! Qualifier for tables stored in ROM */
#define TABLE

/*! Access macro for tables stored in ROM */
#define TABLE_READ(a)	(*a)

/*******************/
/* Platform extras */
/*******************/

/*! Additional platform specific storage declarations */
#define PLATFORM_STORE

/*!
 * Additional platform-specific initialisation, called during
 * \see phy_init
 */
#define PLATFORM_INIT()

/*******/
/* SPI */
/*******/

/*! Function to assert SPI select */
#define SELECT()                                                   \
do {                                                               \
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); \
} while (0)

/*! Function to release SPI select */
#define DESELECT()            \
do {                          \
  SPI.transfer(nSELECT, 0x0); \
  SPI.endTransaction();       \
} while (0)
  

/*! Initialise SPI device */
#define SPI_INIT()	SPI.begin(nSELECT)


/*! Perform single byte transfer on SPI device */
#define SPI_IO(a)		spi_io(a)

static inline uint8_t spi_io(uint8_t data)
{
  return SPI.transfer(nSELECT, data, SPI_CONTINUE);
}

/********************/
/* Power management */
/********************/

/*! Function to enter shutdown */
#define POWER_DOWN()	SETP(TRX_SDN)

/*! Function to release shutdown */
#define POWER_UP()		CLEARP(TRX_SDN)

#endif /* TINYHAN_PLATFORM_H_ */
