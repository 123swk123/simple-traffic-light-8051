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
 
#include "logic_master.h"

#ifdef TRAFFIC_LOGIC_STATE_MACHINE
typedef enum {
	STATE_PRE_WAIT,
	STATE_PRE_STOP,
	STATE_POST_WAIT,
	STATE_POST_GO
} eTrafficState;

eTrafficState gTrafficState = STATE_PRE_WAIT;
#endif

uint8_t gLaneIdx = 0;
tTrafficLED garru8LightState[TRAFFIC_LIGHT_MAX_LANES];
uint8_t gTrafficTickCounter = 0;	//for init, we want to start the logic as quick as possible

#define logicMasterChangeNextLane()	gLaneIdx++;gLaneIdx %= TRAFFIC_LIGHT_MAX_LANES

void logicMasterUpdateLights(void);

void logicMasterInit(void)
{
	memcpy(&garru8LightState[0], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
	memcpy(&garru8LightState[1], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
	memcpy(&garru8LightState[2], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
	memcpy(&garru8LightState[3], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
	logicMasterUpdateLights();
}

void logicMasterUpdateLights(void)
{
	uint8_t* pu8 = (uint8_t*)&garru8LightState;
	uint8_t i = TRAFFIC_LIGHT_MAX_LANES;
	while(i--)
	{
		drvLed1Byte(*pu8++);
		drvLed1Byte(*pu8++);
		drvLed1Byte(*pu8++);
	}
}

//ISR for self wake-up timer
void logicMasterLaneTimeout_ISR (void)   interrupt 17
{
	_push_(SFRS);
	if(!gTrafficTickCounter)
	{
#ifndef TRAFFIC_LOGIC_STATE_MACHINE
		// show wait
		memcpy(&garru8LightState[gLaneIdx], TRAFFIC_WAIT_LED_COLOR, sizeof(tTrafficLED));
		logicMasterUpdateLights();
		Timer0_Delay(24000000,1000*TRAFFIC_SIGNAL_CHANGE_TIMEOUT,1000);
		
		// show stop
		memcpy(&garru8LightState[gLaneIdx], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
		logicMasterUpdateLights();
		Timer0_Delay(24000000,1000*TRAFFIC_SIGNAL_CHANGE_TIMEOUT,1000);
		
		// change lane
		logicMasterChangeNextLane();
		
		// show wait
		memcpy(&garru8LightState[gLaneIdx], TRAFFIC_WAIT_LED_COLOR, sizeof(tTrafficLED));
		logicMasterUpdateLights();
		Timer0_Delay(24000000,1000*TRAFFIC_SIGNAL_CHANGE_TIMEOUT,1000);
		
		// show go
		memcpy(&garru8LightState[gLaneIdx], TRAFFIC_GO_LED_COLOR, sizeof(tTrafficLED));
		logicMasterUpdateLights();
		Timer0_Delay(24000000,1000*TRAFFIC_SIGNAL_CHANGE_TIMEOUT,1000);

		gTrafficTickCounter = TRAFFIC_LANE_CHANGE_TIMEOUT;
#else
		switch(gTrafficState)
		{
			case STATE_PRE_WAIT:
				// show wait
				memcpy(&garru8LightState[gLaneIdx], TRAFFIC_WAIT_LED_COLOR, sizeof(tTrafficLED));
				// use TRAFFIC_SIGNAL_CHANGE_TIMEOUT for time-out
				gTrafficTickCounter = 0;
				gTrafficState = STATE_PRE_STOP;
				break;
			case STATE_PRE_STOP:
				// show wait
				memcpy(&garru8LightState[gLaneIdx], TRAFFIC_STOP_LED_COLOR, sizeof(tTrafficLED));
				// use TRAFFIC_SIGNAL_CHANGE_TIMEOUT for time-out
				gTrafficTickCounter = 0;
				logicMasterChangeNextLane();
				gTrafficState = STATE_POST_WAIT;
				break;
			case STATE_POST_WAIT:
				// show wait
				memcpy(&garru8LightState[gLaneIdx], TRAFFIC_WAIT_LED_COLOR, sizeof(tTrafficLED));
				// use TRAFFIC_SIGNAL_CHANGE_TIMEOUT for time-out
				gTrafficTickCounter = 0;
				gTrafficState = STATE_POST_GO;
				break;
			case STATE_POST_GO:
				// show wait
				memcpy(&garru8LightState[gLaneIdx], TRAFFIC_GO_LED_COLOR, sizeof(tTrafficLED));
				// use TRAFFIC_LANE_CHANGE_TIMEOUT for time-out
				gTrafficTickCounter = TRAFFIC_LANE_CHANGE_TIMEOUT;
				gTrafficState = STATE_PRE_WAIT;
				break;
			default:	/*for safety*/
				gTrafficState = STATE_PRE_STOP;
				break;
		}
		logicMasterUpdateLights();
#endif
	}
	else
	{
		gTrafficTickCounter--;
	}
	clr_WKTF;

	_pop_(SFRS);
}
