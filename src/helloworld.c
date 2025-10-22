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
#include "logic_master.h"

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    drvInit();
    
    logicMasterInit();
    EA = 1;
    while(1);
}

#include "driver.h"
#include "logic_master.h"

void main (void) 
{
	MODIFY_HIRC(HIRC_24);
	drvInit();
	
	logicMasterInit();
	EA = 1;
	while(1);
}
