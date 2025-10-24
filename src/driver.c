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

void drvInit(void)
{
	
	uint8_t hircmap0, hircmap1;
  // SFRS = 0 @ reset
  
  AUXR1 = 0x00;
  
  // read 24MHz calibration trim
  //set_CHPCON_IAPEN;
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	ORL CHPCON, #0x01
	#pragma ENDASM
	
  IAPAL = LOBYTE(0x38);
  IAPAH = HIBYTE(0x38);
  IAPCN = READ_UID;
	//set_IAPTRG_IAPGO;
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	ORL IAPTRG, #0x01
	#pragma ENDASM
  hircmap0 = IAPFD;
  IAPAL++;
  //set_IAPTRG_IAPGO;
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	ORL IAPTRG, #0x01
	#pragma ENDASM
  hircmap1 = IAPFD;
	
	//clr_CHPCON_IAPEN;
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	ANL CHPCON, #0xFE
	#pragma ENDASM
	
  // change HIRC to 24MHz
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	#pragma ENDASM
	RCTRIM1 = hircmap1;
	
	#pragma ASM
	MOV TA, #0xAA
	MOV TA, #0x55
	#pragma ENDASM
	RCTRIM0 = hircmap0;

	P00_PUSHPULL_MODE;                            // P00 (MOSI) Push-Pull mode

	// initialize Wake-up timer to timeout for 1 sec tick resolution
	RWK = 0xFF - (TRAFFIC_TICK_RESOLUTION*5);
	WKCON = 0x0F;	//start timer @ 1:2048 => 4.88Hz(205ms)
	EIE1 = 0x04;
}
