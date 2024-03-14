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

// ---------------------------- TEXT RESPONSE FUNCTIONS ----------------------------

void printVersionInfo() // Sends Current version String Back to the PC
{
  Serial.println(VersionString);
}

void printCurrentAzimuth() // Sends Current Azimuth Angle Back to the PC and LCD
{
  Serial.print("Az"); Serial.print(curAz); Serial.print(".0 "); //Sent to Serial monitor back to PC
  lcd.setCursor(10,2); lcd.print("  "); // Clear the Old Az Characters
  lcd.setCursor(9,2); lcd.print(curAz); // Displays current Az on LCD and updates while other text stays static
  lcd.setCursor(12,2); lcd.print((char)223); // Print Special Character for Degree

  // Compass Functionality for Az
  if (curAz > 0 && curAz < 15) // North
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(0); lcd.print(" N");
  }
  
  if (curAz > 15 && curAz < 75) // Degree from north towards east direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(1); lcd.print(" NE");
  }
  
  if (curAz > 75 && curAz < 115) // East
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(2); lcd.print(" E");
  }
  
  if (curAz > 115 && curAz < 165) // Degree from south towards east direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(3); lcd.print(" SE");
  }
  
  if (curAz > 165 && curAz < 195) // South
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(4); lcd.print(" S");
  }
  
  if (curAz > 195 && curAz < 235) // Degree from south towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(5); lcd.print(" SW");
  }
  
  if (curAz > 235 && curAz < 285) // West
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(6); lcd.print(" W");
  }
  
  if (curAz > 285 && curAz < 345)    // Degree from North towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(7); lcd.print(" NW");
  }
  
  if (curAz > 345 && curAz < 360)    // Degree from North towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(0); lcd.print(" N");
  }
}

void printCurrentElevation() // Sends the current elevation angle back to the PC and LCD
{
  Serial.print("El"); Serial.print(curEl); Serial.print(".0 "); //Sent to Serial monitor back to PC
  lcd.setCursor(10,3); lcd.print("  "); // Clear the Old Az Characters
  lcd.setCursor(9,3); lcd.print(curEl); // Displays current El on LCD and updates while other text stays static
  lcd.setCursor(12,3); lcd.print((char)223); // Print Special Character for Degree
  
  // Compass Functionality for El
  if (curEl > 180 && curAz < 360) // Below Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(4); lcd.print(" BH");
  }
  
  if (curEl > 0 && curEl < 30) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(6); lcd.print(" H");
  }
  
  if (curEl > 30 && curEl < 65) // From 45 to 90 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(7); lcd.print(" AH");
  }
  
  if (curEl > 65 && curEl < 115) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(0); lcd.print(" OH");
  }
    
  if (curEl > 115 && curEl < 150) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(1); lcd.print(" AH");
  }
    
  if (curEl > 150 && curEl < 180) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(2); lcd.print(" H");
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
  }
}

// Sends the current values of the system parameters back to the PC
void printSetParameters()
{
  Serial.println("System Parameters:");
  printMotorParameters();
  Serial.println();
}

// Sends the current AOS back to the PC
//void printAOSInfo() {
//  Serial.print("AOS");
//  Serial.print(AOS);
//  lcd.setCursor(8,0);
//  lcd.print(AOS);
//}

// Sends the current LOS back to the PC
//void printLOSInfo() {
//  Serial.print("LOS");
//  Serial.print(LOS);
//  lcd.setCursor(8,1);   
//  lcd.print(LOS);
//}
//////////////////////////////////////////////////////////////////////////////////////
