/* ==========================================================================

Amateur Radio Satellite Tracking System using Arduino by Umesh Ghodke
https://sites.google.com/site/k6vugdiary/

Copyright (C) 2012 Umesh Ghodke, Amateur Call Sign K6VUG

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software 
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
MA 02110-1301, USA.

The content is covered under the Creative Commons Attribution-ShareAlike 3.0 
License (http://creativecommons.org/licenses/by-sa/3.0/)

========================================================================== */

#include <EEPROM.h>

// ---------------------------- EEPROM READ/WRITE FUNCTIONS ----------------------------

void writeWordToEEPROM(int addr, int intValue)
{
  byte lsbValue = unsigned(intValue) & 0x00FF;
  byte msbValue = unsigned(intValue) >> 8;
  EEPROM.write(addr, lsbValue);
  EEPROM.write(addr+1, msbValue);
}

int readWordFromEEPROM(int addr)
{
  byte lsbValue, msbValue;
  int intValue;
  lsbValue = EEPROM.read(addr);
  msbValue = EEPROM.read(addr+1);
  intValue = (msbValue << 8) + lsbValue;
  return intValue;
}
//////////////////////////////////////////////////////////////////////////////////////
