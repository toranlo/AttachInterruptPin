/* AttachInterruptPinTest.ino v1.0, 04/04/2022, Jesus Macias
--------------------------------------------------------------------------------
 Example for testing the interrupts on all pins of Arduino Uno, Nano, Mini and
 other 328-based boards.
 To run the Interrupt tests connect a push buton between the pin to test and
 ground, pressing the button the corresponding counter will increment.
 Enter a number from 0 to 7 to run the interruption tests.

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

//getKey----------------------------------------------------------------
/* getKey, 23/02/2022, Jesus Macias
 * Reads a key and discharge the rest of keys until '\n' is found
 * Returns -1 if no key is available
 * Returns 0 if only '\n' is found
 */
int getKey()
{
int key;
  if ((key=Serial.read())==-1) return(-1);
  if (key=='\n') return '\0';
  while (Serial.read()!='\n');
  return(key);
}
//-----------------------------------------------------------------------
//printf-----------------------------------------------------------------
# include <stdio.h>

int serial_putc(char c, FILE *) 
{
  Serial.write(c);
  return c;
} 

void printfBegin(void)
{
  fdevopen(&serial_putc, 0);
}
//------------------------------------------------------------------------

volatile byte int0, int1, int2;
void ISRint0()
{
  int0++;
}
void ISRint1()
{
  int1++;
}
void ISRint2()
{
  int2++;
}

// the setup function runs once when you press reset or power the board
int key;

void setup() {
  Serial.begin(9600);
  printfBegin();
  
  printf("\n");
  printf("To run the Interruption tests connect a push buton between the pin\n");
  printf("to test and ground, pressing the button the corresponding counter\n");
  printf("will increment.\n");
  printf("Enter a number from 0 to 7 to run the interruption tests:\n");

  while ((key=getKey())==-1);
}


// Pins : X   X  2  3  4  5 6 7  PCINT2
//        8   9 10 11 12 13 X X  PCINT0
//        14 15 16 17 18 19 X X  PCINT1
//       (A0 A1 A2 A3 A4 A5 X X)
// the loop function runs over and over again forever
void loop() {
  byte lint0, lint1, lint2, bit;

  int0=int1=int2=lint0=lint1=lint2=0;
  bit=key-'0';
  switch (bit) {
  case 0: //Pin 0 is RX and cannot be tested
  case 1: //Pin 1 is TX and cannot be tested
      printf("Test pins %c, %i, A%i\n",'-',8+bit,bit);
      //pinMode(bit,INPUT_PULLUP);
      pinMode(bit+8,INPUT_PULLUP);
      pinMode(bit+14,INPUT_PULLUP);
      //attachInterruptPin(bit,ISRint2);
      attachInterruptPin(bit+8,ISRint0);
      attachInterruptPin(bit+14,ISRint1);
      printf("pin %i=%s, pin %i=%3i, pin A%i=%3i\n",bit,"---",bit+8,lint0,bit,lint1);
      while ((key=getKey())==-1)
      {
        if (int0!=lint0 || int1!=lint1 || int2!=lint2)
        {
          lint0=int0;
          lint1=int1;
          lint2=int2;
          printf("pin %i=%s, pin %i=%3i, pin A%i=%3i\n",bit,"---",bit+8,lint0,bit,lint1);
        }
      }
        //detachInterruptPin(bit);
      detachInterruptPin(bit+8);
      detachInterruptPin(bit+14);
    break;
  case 2:
  case 3:
  case 4:
  case 5:
      printf("Test pins %i, %i, A%i\n",bit,8+bit,bit);
      pinMode(bit,INPUT_PULLUP);
      pinMode(bit+8,INPUT_PULLUP);
      pinMode(bit+14,INPUT_PULLUP);
      attachInterruptPin(bit,ISRint2);
      attachInterruptPin(bit+8,ISRint0);
      attachInterruptPin(bit+14,ISRint1);
      printf("pin %i=%3i, pin %i=%3i, pin A%i=%3i\n",bit,lint2,bit+8,lint0,bit,lint1);
      while ((key=getKey())==-1)
      {
        if (int0!=lint0 || int1!=lint1 || int2!=lint2)
        {
          lint0=int0;
          lint1=int1;
          lint2=int2;
          printf("pin %i=%3i, pin %i=%3i, pin A%i=%3i\n",bit,lint2,bit+8,lint0,bit,lint1);
        }
      }
      detachInterruptPin(bit);
      detachInterruptPin(bit+8);
      detachInterruptPin(bit+14);
    break;
  case 6:
  case 7:
      printf("Test pins %i, %c, %c\n",bit,'-','-');
      pinMode(bit,INPUT_PULLUP);
      //pinMode(bit+8,INPUT_PULLUP);
      //pinMode(bit+14,INPUT_PULLUP);
      attachInterruptPin(bit,ISRint2);
      //attachInterruptPin(bit+8,ISRint0);
      //attachInterruptPin(bit+14,ISRint1);
      printf("pin %i=%3i, pin -=---, pin -=---\n",bit,lint2);
      while ((key=getKey())==-1)
      {
        if (int0!=lint0 || int1!=lint1 || int2!=lint2)
        {
          lint0=int0;
          lint1=int1;
          lint2=int2;
          printf("pin %i=%3i, pin -=---, pin -=---\n",bit,lint2);
        }
      }
      detachInterruptPin(bit);
      //detachInterruptPin(bit+8);
      //detachInterruptPin(bit+14);    
    break;
  default:
    while ((key=getKey())==-1);
    break;
  }
}

