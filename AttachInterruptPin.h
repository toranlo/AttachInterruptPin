/* AttachInterruptPin v1.0, 04/04/2022, Jesús Macias
 
 AttachInterrupt for all pins of Arduino Uno, Nano, Mini and other 328-based
 boards. The Arduino attachInterrupt() function only allows pines 2 & ~3.
 Interrupt is trigered by a pin change status (rising or falling edge).
 One or more pins can be combined to activate the same interrupt
 PCINT0 (higher priority): Arduino Uno pins 13,12,~11,~10,~9,8.
 PCINT1                  : Arduino Uno pins A5,A4,A3,A2,A1,A0.
 PCINT2 (lower priority) : Arduino Uno pins 7,~6,~5,4,~3,2,1TX,0RX.
 
 (C) 2022 Jesus Macias

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ATTACHINTERRUPTPIN_H
#define ATTACHINTERRUPTPIN_H

// pin=            0,  1  ,2, 3,4, 5, 6,7,8, 9, 10, 11,12,13,14,15,16,17,18,19 
// Arduino UNO pin=0RX,1TX,2,~3,4,~5,~6,7,8,~9,~10,~11,12,13,A0,A1,A2,A3,A4,A5
// Returns 0 if OK, -1 if error.
int attachInterruptPin(uint8_t pin, void (*userFunc)(void));


// pin=            0,  1  ,2, 3,4, 5, 6,7,8, 9, 10, 11,12,13,14,15,16,17,18,19 
// Arduino UNO pin=0RX,1TX,2,~3,4,~5,~6,7,8,~9,~10,~11,12,13,A0,A1,A2,A3,A4,A5
// Returns 0 if OK, -1 if error.
int detachInterruptPin(uint8_t pin);

#endif
