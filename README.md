# AttachInterruptPin
## AttachInterrupt for all pins of Arduino Uno, Nano, Mini and other 328-based boards.

AttachInterruptPin v1.0, 04/04/2022, toranlo
--------------------------------------------------------------------------------

This is an Arduino library that enables you attach an interrupt to any pin of 
Arduino Uno, Nano, Mini and other 328-based 
boards.
The Arduino attachInterrupt() function only allows pines 2 & ~3.

Interrupt is trigered by a pin change status (rising or falling edge).
One or more pins can be combined to activate the same interrupt:
 - PCINT0 (higher priority): Arduino Uno pins 13,12,~11,~10,~9,8.
 - PCINT1                  : Arduino Uno pins A5,A4,A3,A2,A1,A0.
 - PCINT2 (lower priority) : Arduino Uno pins 7,~6,~5,4,~3,2,1TX,0RX.

To obtain the most recent version of the code or to report issues (or, better, 
provide fixes), please visit the Github pages at

<https://github.com/toranlo/AttachInterruptPin>.


Inquiries via the Github issue tracker, please.  This way, others may benefit
from the answers.

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
