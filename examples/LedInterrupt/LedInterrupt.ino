/* LedInterrupt.ino v1.0, 04/04/2022, Jesus Macias
--------------------------------------------------------------------------------
 Example of using the AttachInteruptPin library.
 Turns ON and OFF a LED diode using pin interrupts.
 In the Arduino Uno connect a push button between pin 4 and GND.

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
#include "AttachInterruptPin.h"

const byte LED_pin=13;
const byte interrupt_pin=4;

// Interrupt function
void ISRint()
{
  // Toggle the LED diode ON and OFF on every change on the pin (rising or 
  // falling edge)
  digitalWrite(LED_pin,(~digitalRead(LED_pin))&0x1);
}

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(LED_pin,OUTPUT);
  digitalWrite(LED_pin,LOW);

  pinMode(interrupt_pin,INPUT_PULLUP);
  delayMicroseconds(10);
  attachInterruptPin(interrupt_pin,ISRint);

  //To detach the interrupt use function detachInterruptPin().
}


// the loop function runs over and over again forever
void loop() {

  //do nothing
}

