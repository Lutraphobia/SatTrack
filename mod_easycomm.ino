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
 * A simple EasyComm II Command Parser
 * A command parser may be constructed in many ways, following  code represents a 
 * very simple version that works by progressively splitting the command string
 * into words and by checking just the first 2 characters of the first word
 * 
 * EasyComm II Commands :
 * AZ      - report AZ position
 * AZnnn.n - move AZ to nnn.n degrees (0 to 360)
 * EL      - report EL position
 * ELnnn.n - move EL to nnn.n degrees (0 to 180)
 * SA      - stop Az rotation
 * SE      - stop El rotation
 * AO      - Display AOS
 * LO      - Display LOS
 * 
 * Configuration Commands :
 * HELP        - show list of commands and current parameter values
 * VER         - show version number of this program
 * SV          - report values of all set parameter values
 * SV DEFAULTS - sets all parameter values to default
 * SV SPD min max default - sets the SPEED parameters for all steppers
 * SV ACC min max default - sets the ACCEL parameters for all steppers
 * SV STEPS nnnn          - sets steps per revolution
 * SV POS nnn nnn         - aligns position values in program to specific values
 * ECHO ON/OFF            - turns echoing characters ON or OFF, used for debugging
 */

// Identify Commands By Checking The First Two Letters
void parseCommands()
{
  int n, iResult;
  str1.trim();
  str1.toUpperCase();
  for (n = 0; n <= 5; n++)
  { 
    str1.replace("\r", " ");
    str1.replace("\n", " ");
    str1.replace("  ", " "); 
  }
  while (str1 != "")
  {
    // extract one command word from input string (separator is SPACE)
    n = str1.indexOf(' ');
    if (n > 0)
    {
      str2 = str1.substring(0,n); // command word
      str1 = str1.substring(n+1); // remaining part of the command string
      str1.trim();
    }
    else
    {
      str2 = str1; // copy the last word
      str1 = "";   // clear command string
    }
    str2.trim();  // remove leading and trailing spaces
    if (str2.startsWith("SA"))  // Stop Az - Azimuth Rotation
    {
      stopMotorAz();
      newAz = curAz;
      printCurrentAzimuth();
    }
    else if (str2.startsWith("SE"))  // Stop El - Elevation Rotation
    {
      stopMotorEl();
      newEl = curEl;
      printCurrentElevation();
    }
    else if (str2.startsWith("AZ"))  // process AZ command
    {
      str2 = str2.substring(2); // get parameters
      if (str2 != "")
      {
        iResult = getInt(str2);  // convert string to integer
        if (iResult >= 0)  // accept only positive converted values
        {
          newAz = iResult;  // save it as the new target position
          while (newAz > 360) { newAz = newAz-360; } // map all angles 0 to 360 degrees
          setNewAz(newAz);
        }
      }
      printCurrentAzimuth();  // respond with current azimuth
    }
    else if (str2.startsWith("EL"))  // Process El - Elevation Command
    {
      str2 = str2.substring(2);  // Get parameters
      if (str2 != "")
      {
        iResult = getInt(str2);  // Convert string to integer
        if (iResult >= 0)        // Accept only positive values
        {
          newEl = iResult;  // save it as the new target position
          while (newEl > 180) { newEl = newEl - 180;  // Map El to 360 degrees - Change back to 90 if needed - replace 360 with 90 - set app accordingly
          }
          setNewEl(newEl);
          }
      }
      printCurrentElevation();  // Respond with current elevation
    }
    else if (str2.startsWith("VE"))  // Report VE - Version Info
    {
      printVersionInfo();
    }
    else if (str2.startsWith("HE"))  // Report HE - Help Info
    {
      printHelpInfo();
    }
    else if (str2.startsWith("SV"))  // Process SV - Set Value command (Defaults, SPD - Speed, ACC - Acceleration, Steps, POS - Postion)
    {
      Serial.println(str1);  // first, echo the command back
      processSetCommands();  // uses globals str1 and str2
    }
    else if (str2.startsWith("ECHO"))  // Process Echo Command
    {
      echoCmds = str1.equalsIgnoreCase("ON");
    }
    else if (str2.startsWith("ZERO"))  // Process Zero Command
    {
      setZeroPositions();
      Serial.print("Positions Set to Zero");
    }
    else  // Ignore all Rest and Return Unknown
    {
      Serial.print(str2);
      Serial.print("? ");
    }
      Serial.print(" ");
    }
}

// Command Syntax: 
void processSetCommands()
{
  int n = 0;
  if (str1 = "")
  {
    printSetParameters();
  }
  if (str1.startsWith("POS"))
  {
    Serial.print("Position override");
    n = str1.indexOf(' ');
    if (n > 0)  // skip "POS" word
    {
      str1 = str1.substring(n+1);  // remaining part of the command string
      str1.trim();
      n = str1.indexOf(' ');
      if (n > 0)
      {
        str2 = str1.substring(0,n);  // azimuth
        str3 = str1.substring(n+1);  // elevation
        str2.trim();
        str3.trim();
        newAz = curAz;
        setNewAz(newAz);
        newEl = curEl;
        setNewEl(newEl);
      }
      else {
        // nothing specified
      }
    }
  }
  str1 = "";  // everything else is ignored
}

// Report AOS - AOS Information
//    else if (str2.startsWith("AO")) {
//      printAOSInfo();
//    }
// End of Report AOS - AOS Information

// Report LOS - LOS Information
//    else if (str2.startsWith("LO")) {
//      printLOSInfo();
//    }
// End of Report LOS - LOS Information

/*  Original
 *   int n, iResult;
      str1.trim();
      str1.toUpperCase();
      while (str1 != "")
      {
        n = str1.indexOf(' ');  // extract one command word from input string (separator is SPACE)
        if (n > 0)
        {
          str2 = str1.substring(0,n);  // command word
          str1 = str1.substring(n+1);  // remaining part of the command string
          str1.trim();
        }
        else
        {
          str2 = str1;  // copy the last word
          str1 = "";  // clear command string
        }
        str2.trim();  // remove leading and trailing spaces
 * 
 * New?
 *         printCurrentAzimuth();  // if there are no parameters, respond with current azimuth
        }
        else
        {
          Serial.print("AZ");  // process the move command, and respond with new position
          Serial.print(str2);
          iResult = getInt(str2);  // Convert string to integer
          if (iResult >= 0)        // Accept only positive converted values
          {
            newAz = iResult;  // Save it as the new target position
            while (newAz > 360) 
            {
              newAz = newAz - 360;  // Map Az to 360 degrees
            }
            setNewAz(newAz);
           }
        }
    }
 */
