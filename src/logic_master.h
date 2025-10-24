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

#ifndef _LOGIC_MASTER_H_
#define _LOGIC_MASTER_H_
#include "driver.h"

// comment out to use non-state machine based logic
#define TRAFFIC_LOGIC_STATE_MACHINE

#define TRAFFIC_LIGHT_MAX_LANES		4

#define TRAFFIC_SIGNAL_CHANGE_TIMEOUT	1	/*10 second; min:1s, max:254s*/
#define TRAFFIC_LANE_CHANGE_TIMEOUT		8	/*1 minute; min:1s, max:254s*/

typedef uint8_t tTrafficLED[BYTES_PER_LED];

extern const tTrafficLED code TRAFFIC_STOP_LED_COLOR;
extern const tTrafficLED code TRAFFIC_WAIT_LED_COLOR;
extern const tTrafficLED code TRAFFIC_GO_LED_COLOR;

void logicMasterInit(void);
uint8_t logicMasterGetNextLane(void);

#endif
