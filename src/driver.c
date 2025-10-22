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

#include "driver.h"

const tTrafficLED code TRAFFIC_STOP_LED_COLOR	=	{0xFF, 0, 0};
const tTrafficLED code TRAFFIC_WAIT_LED_COLOR	=	{0x66, 0x33, 0};
const tTrafficLED code TRAFFIC_GO_LED_COLOR	=	{0, 0xFF, 0};

extern void drvLed1Byte(uint8_t val);

void drvInit(void)
{
	P00_PUSHPULL_MODE;                            // P00 (MOSI) Push-Pull mode

	// initialize Wake-up timer to timeout for 1 sec tick resolution
	RWK = 0xFF - (TRAFFIC_TICK_RESOLUTION*5);
	WKCON = 0x0F;	//start timer @ 1:2048 => 4.88Hz(205ms)
	EIE1 = 0x04;
}
