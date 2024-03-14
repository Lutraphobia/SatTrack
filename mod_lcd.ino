/* ==========================================================================

Amateur Radio Satellite Tracking System using Arduino
LCD Mod by WA7ZYW

Copyright (C) 2012 Umesh Ghodke, Amateur Call Sign K6VUG / Mod by WA7ZYW

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

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c (Library for LCD)

LiquidCrystal_I2C lcd(0x27,20,4); // Address, # Chars, # Rows - Wiring: SDA to A4 and SCL to A5 via I2C, address 0x27

  // Let's Build Some Custom Characters - Can ONLY Have Up to Eight!
  byte north [8] = {0x04,0x0E,0x1F,0x04,0x04,0x04,0x04,0x00};  // build LCD specific characters 'North or Up'
  byte ne [8] = {0x0,0xf,0x3,0x5,0x9,0x10,0x0};  // build LCD specific characters 'Northeast'
  byte east [8] = {0x00,0x04,0x02,0x1F,0x02,0x04,0x00,0x00};  // build LCD specific characters 'East or Right'
  byte se [8] = {0x00,0x00,0x10,0x09,0x05,0x03,0x0F,0x00};  // build LCD specific characters 'Southeast'
  byte south [8] = {0x00,0x04,0x04,0x04,0x04,0x1F,0x0E,0x04};  // build LCD specific characters 'South or Ddown'
  byte sw [8] = {0x00,0x00,0x01,0x12,0x14,0x18,0x1E,0x00};  // build LCD specific characters 'Southwest'
  byte west [8] = {0x00,0x04,0x08,0x1F,0x08,0x04,0x00,0x00};  // build LCD specific characters 'West or Left'
  byte nw [8] = {0x00,0x1E,0x18,0x14,0x12,0x01,0x00,0x00};  // build LCD specific characters 'Northwest'
  // byte degree [8] = {0x0C,0x12,0x12,0x0C,0x00,0x00,0x00,0x00}; // build LCD specific characters 'degrees'
  
void setuplcd()  // Initiate the I2C LCD and Turn on LCD Backlight
{
  lcd.init();
  lcd.backlight();
  
  // Creating Custom Characters
  lcd.createChar(0, north);
  lcd.createChar(1, ne);
  lcd.createChar(2, east);
  lcd.createChar(3, se);
  lcd.createChar(4, south);
  lcd.createChar(5, sw);
  lcd.createChar(6, west);
  lcd.createChar(7, nw);
  // lcd.createChar(8, degree);
  bootlcd();  // Call Boot LCD Sequence 
}

void bootlcd( )//Initial Boot Write to LCD Display about Device
{
  lcd.clear(); // CLS
  lcd.setCursor(0, 0);  // Line 0, Indent 0
  lcd.print("SatTracker by K6VUG");
  lcd.setCursor(3,1);  // Line 1, Indent 0
  lcd.print("Mod by WA7ZYW");
  lcd.setCursor(7,2);  // Line 2, Indent 0
  lcd.print("Happy");
  lcd.setCursor(6,3);  // Line 3, Indent 0
  lcd.print("Tracking");
  delay (10000);  // Wait 10 seconds
  staticlcd();  // Call Static LCD Sequence
}

void staticlcd() // Display Tracking Information - Meant to Stay Static - No Refresh
{
  lcd.clear(); // CLS
  lcd.setCursor(1,0); lcd.print("Selected Satellite");  // Line 0, Indent 1
  lcd.setCursor(2,1); lcd.print("Is Now Tracking:");  // Line 1, Indent 0
  lcd.setCursor(4,2); lcd.print("Az = ");  // Line 2, Indent 6
  lcd.setCursor(4,3); lcd.print("El = ");  // Line 3, Indent 6
}

/* Special Character test
  lcd.setCursor(0,3); lcd.write(0); // Line 3, Indent 0
  lcd.setCursor(2,3); lcd.write(1); // Line 3, Indent 2
  lcd.setCursor(4,3); lcd.write(2); // Line 3, Indent 4
  lcd.setCursor(6,3); lcd.write(3); // Line 3, Indent 6
  lcd.setCursor(8,3); lcd.write(4); // Line 3, Indent 8
  lcd.setCursor(10,3); lcd.write(5); // Line 3, Indent 10
  lcd.setCursor(12,3); lcd.write(6); // Line 3, Indent 12
  lcd.setCursor(14,3); lcd.write(7); // Line 3, Indent 14

  // lcd.setCursor(17,2); lcd.write(0); // Line 2 - Print Degree special character symbol
  // lcd.setCursor(17,3); lcd.write(0); // Line 3 - Print Degree special character symbol
*/
