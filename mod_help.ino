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

// Set Help Strings
String HelpLine1  = "EasyComm Commands:";
String HelpLine2  = "VE(rsion)";
String HelpLine3  = "AZ[nnn.n] (0-360)";
String HelpLine4  = "EL[nn.n]  (0-90)";
String HelpLine5  = "SA (stop AZ)";
String HelpLine6  = "SE (stop EL)";
String HelpLine7  = "HE(lp)";
String HelpLine8  = "ECHO ON/OFF";
String HelpLine9  = "SV (show current values)";
String HelpLine10 = "ZERO"; //"SV DEFAULTS";
String HelpLine11 = "SV STEPS nnn (steps)";
String HelpLine12 = "SV SPEED min max default";
String HelpLine13 = "SV ACCEL min max default";
String HelpLine14 = "Steppers: #1 for AZ, #2 for EL";

void printHelpInfo()  // Respond with the help strings organised as a help page
{
  Serial.println();
  Serial.println(VersionString);
  Serial.println();
  Serial.println(HelpLine1);
  Serial.println(HelpLine2);
  Serial.println(HelpLine3);
  Serial.println(HelpLine4);
  Serial.println(HelpLine5);
  Serial.println(HelpLine6);
  Serial.println(HelpLine7);
  Serial.println(HelpLine8);
  Serial.println(HelpLine9);
  Serial.println(HelpLine10);
  Serial.println(HelpLine11);
  Serial.println(HelpLine12);
  Serial.println(HelpLine13);
  Serial.println();
  Serial.println(HelpLine14);
  //Serial.println();
  printSetParameters();
}
//////////////////////////////////////////////////////////////////////////////////////
