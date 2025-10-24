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
 
//#pragma SRC
//#pragma NOREGPARMS

#include "MS51_16K.H"

sbit ACC0 = ACC^0;
sbit ACC1 = ACC^1;
sbit ACC2 = ACC^2;
sbit ACC3 = ACC^3;
sbit ACC4 = ACC^4;
sbit ACC5 = ACC^5;
sbit ACC6 = ACC^6;
sbit ACC7 = ACC^7;

/*
bit length: 1250ns @ 24MHz => 30cyc
BIT High 1: 750ns @ 24MHz => 18cyc(-12)
BIT Low  1: 330ns @ 24MHz => 8cyc(-22)
*/
void drvLed1Byte(uint8_t r,uint8_t g,uint8_t b)
{
#pragma ASM
	WAIT_CYC MACRO X
		REPT X
			NOP
		ENDM
	ENDM
	
	EMIT_BIT MACRO Cl, X, Y
		Cl&bit&X:
			SETB P0.0							
			//WAIT_CYC 1								//BH=3,BL=3
			JNB ACC.&X, Cl&bit&X&_snd0		//BH+5=8,BL+5=8
			Cl&bit&X&_snd1:
				WAIT_CYC 12							//BH+12=20
				CLR P0.0								//BH+4=24
				WAIT_CYC 2							//BH+2=26
				SJMP Cl&bit&Y							//BH+3=29
			Cl&bit&X&_snd0:
				CLR P0.0								//BL+4=12
				WAIT_CYC 17							//BL+17=29
	ENDM
	
	EMIT_BIT_LAST MACRO Cl, X, Y
		Cl&bit&X:
			SETB P0.0							
			//WAIT_CYC 1								//BH=3,BL=3
			JNB ACC.&X, Cl&bit&X&_snd0		//BH+5=8,BL+5=8
			Cl&bit&X&_snd1:
				WAIT_CYC 10							//BH+8=18
				CLR P0.0								//BH+4=22
				//WAIT_CYC 5							//BH+5=27
				SJMP Cl&bit&Y							//BH+3=30
			Cl&bit&X&_snd0:
				CLR P0.0								//BL+4=12
				WAIT_CYC 13							//BL+18=30
	ENDM
	
	MOV ACC, r?040
	EMIT_BIT r, 7, 6
	EMIT_BIT r, 6, 5
	EMIT_BIT r, 5, 4
	EMIT_BIT r, 4, 3
	EMIT_BIT r, 3, 2
	EMIT_BIT r, 2, 1
	EMIT_BIT r, 1, 0
	EMIT_BIT_LAST r, 0, _end
	rbit_end:
	
	MOV ACC, g?041
	EMIT_BIT g, 7, 6
	EMIT_BIT g, 6, 5
	EMIT_BIT g, 5, 4
	EMIT_BIT g, 4, 3
	EMIT_BIT g, 3, 2
	EMIT_BIT g, 2, 1
	EMIT_BIT g, 1, 0
	EMIT_BIT_LAST g, 0, _end
	gbit_end:
	
	MOV ACC, b?042
	EMIT_BIT b, 7, 6
	EMIT_BIT b, 6, 5
	EMIT_BIT b, 5, 4
	EMIT_BIT b, 4, 3
	EMIT_BIT b, 3, 2
	EMIT_BIT b, 2, 1
	EMIT_BIT b, 1, 0
	EMIT_BIT_LAST b, 0, _end
	bbit_end:
	
#pragma ENDASM
}
