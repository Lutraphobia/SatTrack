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

/*
 * Change log for SatTracker developed by Umesh Ghodke, K6VUG 
 * WA7ZYW changes
 * - Set Parking to Zero Az/El - Ensure your SatTracking program is setup correctly to reflect change from 90 to 0 / HRD, PSTRotator 
 * - Changed El to 180 - Ensure your SatTracking program is setup correctly to reflect change from 90 to 180 / HRD, PSTRotator
 * - Removed AdaFruit Motorshield v2.x stepper commands - setting up steppers with CnC shield v3.0 / drv8825 / NEMA 17 common steppers in 18 microstep
 * - Included CnC Shield Stepper Enable pin in mod_stepper
 * - Tweaked EasyComm implementation (removed For and copied While from other SatTracker - read that While is better at conditions)
 * - Implemented i2c 4x20 status screen with degrees tracked for Az and El
 * - Trying to Add AOS and LOS - don't have defined strings to work with from PSTRotator.
 * 
 * K6VUG Changes
 * - Optimised text and string usage to reduce program size
 * - Implemented parking position for servos on reset (AZ=90, EL=90)
 * - Added handling of BACKSPACE and TAB characters in commands
 * - EEPROM stores calibration settings & configuration values
 * - Added work around for HRD problem with Arduino reset timing
 */

// ----------------------------- CONSTANT DECLARATIONS ---------------------------

// Version string
String VersionString = "AZ/EL Rotator Controller\r\nDeveloped by Umesh Ghodke, K6VUG";

// serial communication
#define BAUDRATE 9600

// degrees
#define PARKPOS_AZ 0  // Was 90
#define PARKPOS_EL 0  // Was 90

// -------------------------------- PROGRAM VARIABLES ----------------------------------

// position control variables
unsigned int curAz, newAz; // positions
unsigned int curEl, newEl; // positions
unsigned int curSpeed;

// misc variables
boolean echoCmds = false;

// temporary variables
String command, str1, str2, str3; // command string from input
char carray[8];                   // character array for string to int manipulation
char inByte;                      // input byte from serial port

// --------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(BAUDRATE);  // initialize serial comm
  Serial.flush();
  setupSteppers();  // initialize motors
  newAz = curAz;  // initialize variables
  newEl = curEl;
  pinMode(13, OUTPUT);  // initialize the digital pin as an output. Pin 13 has an LED connected on most Arduino boards
  digitalWrite(13, LOW);  // turn the LED off
  printCurrentAzimuth();  // Work around for HRD issues due to Arduino board reset timing
  printCurrentElevation();
  Serial.print("\r\n");
  setuplcd();  // initialize LCD
}

void loop()
{
  checkSerialPort(); // check if there are any new commands
  loopSteppers(); // continue moving motors
}

// ---------------------------- SERIAL COMMUNICATION FUNCTIONS ----------------------------

void checkSerialPort()
{
  int n;  
  if (Serial.available() > 0)  // check serial port for new data
  {
    inByte = Serial.read();
    if (echoCmds) Serial.write(inByte);  // echo the character back
    if (inByte == 8)  // Support BACKSPACE(8)
    {
      n = command.length();
      if (n > 0)
      command = command.substring(0,n-1);
    }
    else if (inByte == 9 || inByte == 44)  // Convert TAB(9), COMMA(44) to SPACE(32)
    {
      command.concat(32);
    }
    else if (inByte == 32 || inByte == 46 || (inByte >= 48 && inByte <=57) || (inByte >= 65 && inByte <= 90) || (inByte >=97 && inByte <=122))  // letters(A-Z,a-z), numbers(0-9), SPACE(32), PERIOD(46)
    {
      command.concat(inByte);
    }
    else if (inByte == 10 || inByte == 13)  // Process command when NL/CR received
    {
      inByte = 0;
      str1 = command;  //Parse and respond to commands
      command = "";  // clear the string to accept next command
      parseCommands();
      Serial.print("\n");
      //Serial.println("");
    }
  }
}

// ---------------------------- MATH FUNCTIONS ----------------------------

int getInt(String text)
{
  int x;
  str3 = text;
  str3.trim();
  if ((str3 != "") && (str3.charAt(0) >= '0') && (str3.charAt(0) <= '9'))
  {
    str3.toCharArray(carray, 7);
    x = atoi(carray);
  }
  else
  {
    x = -1;
  }
  return x;
}
//////////////////////////////////////////////////////////////////////////////////////
