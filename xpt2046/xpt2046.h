/**
 @file     xpd2046.h
 @version V0.10
 @date     22 Sept 2016
 
 @brief XPT2046 drivers

 @par Copyright &copy; 2015 Mike Gore, GPL License
 @par You are free to use this code under the terms of GPL
  please retain a copy of this notice in any code you use it in.

  This is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option)
  any later version.
  
  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _XPT2046_H_
#define _XPT2046_H_

///@brief number of time to read and average results
#define XPT2046_SAMPLES 8 	/* make this a power of 2 */
#define XPT2046_DEBOUNCE 10 /* Debound value in mS */
#define XPT2046_EVENTS 10 /* Number of queued touch events */

///@brief only need 4 commands for reading position or touch information
#define XPT2046_READ_Y  0x91    /* Read Y position*/
#define XPT2046_READ_Z1 0xb1	/* Read Z1 */
#define XPT2046_READ_Z2 0xc1    /* read Z2 */
#define XPT2046_READ_X  0xd1	/* Read X position */

typedef struct _xpt2046 
{
	// touch debounce state machine
    int state;  // Debounce state machine
    int ms;     // Debounce 1mS timer

	// touch input queue
    int count;	// touch events
    int head;	// head of touch event queue
    int tail;	// tail of touch event queue
	uint16_t XQ[XPT2046_EVENTS+1];	// Debounced X result
	uint16_t YQ[XPT2046_EVENTS+1];	// Debounced Y result
} xpt2046_t;

typedef struct _sdev {
    uint16_t Min,Max;
    float mean, sdev;
} sdev_t;

/* xpt2046.c */
MEMSPACE void XPT2046_spi_init ( void );
void XPT2046_key_flush ( void );
int XPT2046_key ( uint16_t *X , uint16_t *Y );
uint16_t XPT2046_read ( uint8_t cmd );
int XPT2046_read_filtered ( uint16_t *X , uint16_t *Y );
void XPT2046_task ( void );


#endif // _XPT2046_H_



