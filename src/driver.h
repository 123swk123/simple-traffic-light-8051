/*
 * Copyright (c) 2025 swk (https://github.com/123swk123)
 * Licensed under the MIT License.
 *
 * This file is distributed under the MIT License. You are free to use,
 * reproduce, modify, merge, publish, distribute, sublicense and/or sell
 * copies of this file, provided that this copyright and permission notice
 * are included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "MS51_16K.h"

#define BYTES_PER_LED		3
#define TRAFFIC_TICK_RESOLUTION				1		/*1 second; min:1s, max:50s*/

typedef uint8_t tTrafficLED[BYTES_PER_LED];

extern const tTrafficLED code TRAFFIC_STOP_LED_COLOR;
extern const tTrafficLED code TRAFFIC_WAIT_LED_COLOR;
extern const tTrafficLED code TRAFFIC_GO_LED_COLOR;

void drvInit(void);
extern void drvLed1Byte(uint8_t val);

#endif
