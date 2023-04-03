/* AttachInterruptPin v1.0, 04/04/2022, toranlo
 
 AttachInterrupt for all pins of Arduino Uno, Nano, Mini and other 328-based
 boards. The Arduino attachInterrupt() function only allows pines 2 & ~3.
 Interrupt is trigered by a pin change status (rising or falling edge).
 One or more pins can be combined to activate the same interrupt
 PCINT0 (higher priority): Arduino Uno pins 13,12,~11,~10,~9,8.
 PCINT1                  : Arduino Uno pins A5,A4,A3,A2,A1,A0.
 PCINT2 (lower priority) : Arduino Uno pins 7,~6,~5,4,~3,2,1TX,0RX.
 
 (C) 2022 toranlo

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

#include <avr/io.h>
#include <avr/interrupt.h>

#include "AttachInterruptPin.h"

#if !defined(__AVR_ATmega328P__) && !defined(__AVR_ATmega328__)
#error Only for Arduino Uno, Nano, Mini and other 328-based boards
#endif

void (*isrCallbackPCINT0)();
/* 
 Pin Change Interrupcion 0 for PCINT[7:0] ATMega328P pins, in Arduino UNO pins 
 -, -, 13, 12, ~11, ~10, ~9, 8.
*/
ISR(PCINT0_vect)
{
  isrCallbackPCINT0();
}

void (*isrCallbackPCINT1)();
/* 
 Pin Change Interrupcion 1 for PCINT[14:08] ATMega328P pins, in Arduino UNO pins
 19(A5), 18(A4), 17(A3), 16(A2), 15(A1), 14(A0). 
 
*/
ISR(PCINT1_vect)
{
  isrCallbackPCINT1();
}

void (*isrCallbackPCINT2)();
/* 
 Pin Change Interrupcion 2 for PCINT[23:16] ATMega328P pins, in Arduino UNO pins 
 7, ~6, ~5, 4, ~3, 2, 1, 0.
*/
ISR(PCINT2_vect)
{
  isrCallbackPCINT2();
}



// pin=            0,  1  ,2, 3,4, 5, 6,7,8, 9, 10, 11,12,13,14,15,16,17,18,19 
// Arduino UNO pin=0RX,1TX,2,~3,4,~5,~6,7,8,~9,~10,~11,12,13,A0,A1,A2,A3,A4,A5
// Returns 0 if OK, -1 if error.
int attachInterruptPin(uint8_t pin, void (*userFunc)(void))
{ 
  if (pin >=0 && pin <=7)
  {
    //PCINT2: ATmega328P PCINT[23:16], Arduino Uno pins 7,-6,-5,4,-3,2,1TX,0RX
    
    //Enable the pin
    PCMSK2|=1<<pin;
    
    //Assign callback
    isrCallbackPCINT2=userFunc;
    
    //Enable interrupt
    PCICR|=1<<PCIE2;
    
  } else if (pin >= 8 && pin<=13)
  {
    //PCINT0: ATmega328P PCINT[7:0], Arduino Uno pins -,-,13,12,-11,-10,-9,8

    //Enable the pin
    PCMSK0|=1<<(pin-8);

    //Assign callback
    isrCallbackPCINT0=userFunc;
    
    //Enable interrupt
    PCICR|=1<<PCIE0;

  } else if (pin >= 14 && pin <= 19)
  {
    //PCINT1: ATmega328P PCINT[14:8], Arduino Uno pins -,A5,A4,A3,A2,A1,A0

    //Enable the pin
    PCMSK1|=1<<(pin-14);

    //Assign callback
    isrCallbackPCINT1=userFunc;
    
    //Enable interrupt
    PCICR|=1<<PCIE1;

  } else return(-1); 
}

// pin=            0,  1  ,2, 3,4, 5, 6,7,8, 9, 10, 11,12,13,14,15,16,17,18,19 
// Arduino UNO pin=0RX,1TX,2,~3,4,~5,~6,7,8,~9,~10,~11,12,13,A0,A1,A2,A3,A4,A5
// Returns 0 if OK, -1 if error.
int detachInterruptPin(uint8_t pin)
{
  
  if (pin >=0 && pin <=7)
  {
    //PCINT2

    //Disable the pin
    PCMSK2&=~(1<<pin);

    //Disable interrupt
    PCICR&=~(1<<PCIE2);
    
  } else if (pin >= 8 && pin<=13)
  {
    //PCINT0

    //Disable the pin
    PCMSK0&=~(1<<(pin-8));

    //Disable interrupt
    PCICR&=~(1<<PCIE0);
    
  } else if (pin >= 14 && pin <= 19)
  {
    //PCINT1

    //Disable the pin
    PCMSK1&=~(1<<(pin-14));

    //Disable interrupt
    PCICR&=~(1<<PCIE1);
    
  } else return(-1);
}
